#include "GameHooks.h"
#include "SubContext.h"

typedef int(__thiscall* func_BGM)(void*, int, int, int, int, int, int, int);
typedef int(__cdecl* func_BGM2)(int, float, float);
typedef int(__cdecl* func_ResetBGM)(int);
typedef INT_PTR(__stdcall* func_VersionDialogProc)(HWND, UINT, WPARAM, LPARAM);

func_BGM orig_BGM;
func_BGM2 orig_BGM2;
func_ResetBGM orig_ResetBGM;
func_VersionDialogProc orig_VersionDialogProc;

SubContext subContext;

int bgm = 0, chapter = 0;

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

int __fastcall hook_BGM(void* _this, int _edx, int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
	int result = orig_BGM(_this, a1, a2, a3, a4, a5, a6, a7);
#ifdef _DEBUG
	currentInd ^= 1;
	sprintf_s<100>(audioInd[currentInd], "BGM: %d Chapter: %d", a2, *(int*)0xA6FDE4);
	char str[100];
	sprintf_s<100>(str, "WHITE ALBUM2 Special Contents [%s | %s]", audioInd[currentInd], audioInd[currentInd ^ 1]);
	SetWindowTextA(*(HWND*)0x4BF350, str);
#endif
	// We need voice dramas only...
	if (a2 >= 80)
	{
		bgm = a2;
		chapter = *(int*)0xA6FDE4;
		subContext.tryPlay(bgm << 16 | chapter);
	}
	return result;
}

// We need this function to detect the automatic chapter switch.
int __cdecl hook_BGM2(int a1, float a2, float a3)
{
	int result = orig_BGM2(a1, a2, a3);
	if (a2 == 0.0f && a3 == 64.0f && chapter != *(int*)0x4BF2D0)
	{
#ifdef _DEBUG
		currentInd ^= 1;
		sprintf_s<100>(audioInd[currentInd], "BGM: %d Chapter: %d", bgm, *(int*)0x4BF2D0);
		char str[100];
		sprintf_s<100>(str, "WHITE ALBUM2 Special Contents [%s | %s]", audioInd[currentInd], audioInd[currentInd ^ 1]);
		SetWindowTextA(*(HWND*)0x4BF350, str);
#endif
		chapter = *(int*)0x4BF2D0;
		if (subContext.tryPlay(bgm << 16 | chapter))
			subContext.shiftBeginTime(1000); // There is a 1 sec delay between function call and audio play.
	}
	return result;
}

int __cdecl hook_ResetBGM(int a1)
{
	int result = orig_ResetBGM(a1);
	subContext.isSubPlaying = false;
	subContext.isSongPlaying = false;
	return result;
}

INT_PTR __stdcall hook_VersionDialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	INT_PTR result = orig_VersionDialogProc(hwnd, uMsg, wParam, lParam);
	if (uMsg == WM_INITDIALOG)
	{
		wchar_t str[100];
		GetWindowTextW(hwnd, str, 100);
		wcscat_s<100>(str, L" ×ÖÄ»²¹¶¡°æ±¾1.0");
		SetWindowTextW(hwnd, str);
	}
	return result;
}

// The "reset" function is used to determine when audios are stopped.
// Since it is called when any audio is stopped (and sometimes something else), we need address as extra info.
void setGameHooks()
{
	orig_BGM = (func_BGM)setHook((char*)hook_BGM, (char*)0x460BB0, 6);
	orig_BGM2 = (func_BGM2)setHook((char*)hook_BGM2, (char*)0x44B790, 6);
	orig_ResetBGM = (func_ResetBGM)setHook((char*)hook_ResetBGM, (char*)0x406A30, 6);
	// version info dialog callback function. hook to add patch version to title 
	orig_VersionDialogProc = (func_VersionDialogProc)setHook((char*)hook_VersionDialogProc, (char*)0x431F10, 9);
}