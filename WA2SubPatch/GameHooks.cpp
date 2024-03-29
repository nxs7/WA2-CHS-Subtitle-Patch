#include "GameHooks.h"
#include "SubContext.h"

typedef void(__cdecl* func_SoundEffect)(int, int, int, int, int, int);
typedef int(__cdecl* func_Voice)(int, int, int, int, int, int, int);
typedef int(__cdecl* func_Interview)(int, int);
typedef int(__cdecl* func_Reset)(int, int);
typedef INT_PTR(__stdcall* func_VersionDialogProc)(HWND, UINT, WPARAM, LPARAM);

func_SoundEffect orig_SoundEffect;
func_Voice orig_Voice;
func_Interview orig_Interview;
func_Reset orig_ResetSE;
func_Reset orig_ResetVoice;
func_VersionDialogProc orig_VersionDialogProc;

SubContext subContext;

int seAddress = 0, voiceAddress = 0;

#ifdef _DEBUG
char audioInd[2][100];
int currentInd = 0;
#endif

void initSub(IDirect3DDevice9* device)
{
	subContext = SubContext(device);
}

void update()
{
	subContext.update();
}

char* setHook(char* dst, char* src, size_t len)
{
	DWORD orig;
	char* trampo = (char*)VirtualAlloc(NULL, len + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	memcpy(trampo, src, len);
	*(trampo + len) = 0xE9; // jmp
	*(int*)(trampo + len + 1) = src - trampo - 5; // (src + len) - (trampo + len + 5)

	VirtualProtect(src, 5, PAGE_READWRITE, &orig);
	*src = 0xE9;
	*(int*)(src + 1) = dst - src - 5; // dst - (src + 5)
	VirtualProtect(src, 5, orig, &orig);

	return trampo;
}

// These logics are from IDA, so ask Hex-Rays if they look weird.
void __cdecl hook_SoundEffect(int a1, int a2, int a3, int a4, int a5, int a6)
{
	orig_SoundEffect(a1, a2, a3, a4, a5, a6);
#ifdef _DEBUG
	currentInd ^= 1;
	sprintf_s<100>(audioInd[currentInd], "SE: %d", a2);
	char str[100];
	sprintf_s<100>(str, "WHITE ALBUM2 [%s | %s]", audioInd[currentInd], audioInd[currentInd ^ 1]);
	SetWindowTextA(*(HWND*)0x4C2224, str);
#endif
	if (!subContext.isPlaying)
	{
		// The original author stated that the scene ID becomes a must 
		// when there are conflicts.
		// Eg. sound effect 9777 was used 3 times in scene 1013, 2516
		// and 3110. However, in scene 3110, it was truncated in the
		// first sentence, making its sub differentfrom the others.
		// However, here we used function calls instead of lines as 
		// triggers of stop of the audios. Therefore, the sub will
		// automaticly be stopped, with no conflicts anymore.
		// (Is this really not just a clerical error?)
		// 
		// Situation is similar in the following voice hook.
		int se = a2;
		if (subContext.tryPlay(se, false))
			seAddress = 0x5E7364 + 52 * a1;
	}
}

int __cdecl hook_Voice(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
	int result = orig_Voice(a1, a2, a3, a4, a5, a6, a7);
#ifdef _DEBUG
	currentInd ^= 1;
	sprintf_s<100>(audioInd[currentInd], "Scene: %d Voice: %d", a3 == -1 ? (*(int*)0x4BE4CC == -1 ? *(int*)0xA391E0 : *(int*)0x4BE4CC) : a3, *(int*)0xA391EC + a4);
	char str[100];
	sprintf_s<100>(str, "WHITE ALBUM2 [%s | %s]", audioInd[currentInd], audioInd[currentInd ^ 1]);
	SetWindowTextA(*(HWND*)0x4C2224, str);
#endif
	if (!subContext.isPlaying)
	{
		// The scene here is NOT always the same as the the actual scene.
		// It could be different when the voice is used more than once.
		// Eg. voice 8000 of scene 2033 is reused in scene 3003, while
		// its scene is always 2033, wherever it is played.
		// The advantage of using the "local" scene is that a voice 
		// only need to be subbed once, however many times it is played.
		int scene = a3 == -1 ? (*(int*)0x4BE4CC == -1 ? *(int*)0xA391E0 : *(int*)0x4BE4CC) : a3;
		int voice = *(int*)0xA391EC + a4;
		if (subContext.tryPlay(scene << 16 | voice, true))
			voiceAddress = 0xA390D4 + 56 * a1;
	}
	return result;
}

int __cdecl hook_Interview(int a1, int a2)
{
	int result = orig_Interview(a1, a2);
#ifdef _DEBUG
	currentInd ^= 1;
	sprintf_s<100>(audioInd[currentInd], "Interview: %d", a1 - 1);
	char str[100];
	sprintf_s<100>(str, "WHITE ALBUM2 [%s | %s]", audioInd[currentInd], audioInd[currentInd ^ 1]);
	SetWindowTextA(*(HWND*)0x4C2224, str);
#endif
	// SE or voice shouldn't be playing,
	// so there's no need to check.
	//
	// Consider the interview as voice since
	// they share the same reset function.
	//
	// 9500 is "scene number" of the interview,
	// used here to avoid conflict.
	subContext.tryPlay(9500 << 16 | a1 - 1, true);
	// 0xA390D8, 0xA390EC, 0xA390E8 should all be fine.
	voiceAddress = 0xA390D8;
	return result;
}

int __cdecl hook_ResetSE(int a1, int a2)
{
	int result = orig_ResetSE(a1, a2);
	if (subContext.isPlaying && !subContext.isVoicePlaying)
		if (seAddress - (0x5E7360 + 52 * a1) == 4)
			subContext.isPlaying = false;
	return result;
}

int __cdecl hook_ResetVoice(int a1, int a2)
{
	int result = orig_ResetVoice(a1, a2);
	if (subContext.isPlaying && subContext.isVoicePlaying)
	{
		int offset = voiceAddress - (0xA390C8 + 56 * a1);
		if (offset == 12 || offset == 16) // 12 for ordinary voice; 16 for interview
			subContext.isPlaying = false;
	}
	return result;
}

INT_PTR __stdcall hook_VersionDialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	INT_PTR result = orig_VersionDialogProc(hwnd, uMsg, wParam, lParam);
	if (uMsg == WM_INITDIALOG)
	{
		wchar_t str[100];
		GetWindowTextW(hwnd, str, 100);
		wcscat_s<100>(str, L" ��Ļ�����汾0.3");
		SetWindowTextW(hwnd, str);
	}
	return result;
}

// The two "reset" functions are used to determine when audios are stopped.
// Since they are called when any audio is stopped (and sometimes something else), we need address as extra info.
void setGameHooks()
{
	// 0x4058F0 is fine and probably the "original" one, but we need the address which it doesn't offer
	orig_SoundEffect = (func_SoundEffect)setHook((char*)hook_SoundEffect, (char*)0x40F400, 9);
	orig_Voice = (func_Voice)setHook((char*)hook_Voice, (char*)0x40EDA0, 6);
	orig_Interview = (func_Interview)setHook((char*)hook_Interview, (char*)0x406270, 6);
	orig_ResetSE = (func_Reset)setHook((char*)hook_ResetSE, (char*)0x40F590, 6);
	orig_ResetVoice = (func_Reset)setHook((char*)hook_ResetVoice, (char*)0x40EC30, 5);
	// version info dialog callback function. hook to add patch version to title 
	orig_VersionDialogProc = (func_VersionDialogProc)setHook((char*)hook_VersionDialogProc, (char*)0x430A00, 6);
}