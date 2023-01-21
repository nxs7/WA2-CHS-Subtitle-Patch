#include "Direct3DWrapper.h"

typedef IDirect3D9* (WINAPI* func_Direct3DCreate9)(UINT);

extern "C" IDirect3D9 * WINAPI Direct3DCreate9(UINT SDKVersion)
{
	char path[MAX_PATH];
	GetSystemDirectoryA(path, MAX_PATH);
	strcat_s<MAX_PATH>(path, "\\d3d9.dll");
	HMODULE d3d9 = LoadLibraryA(path);
	if(!d3d9)
	{
		MessageBoxW(NULL, L"ÏµÍ³¶¯Ì¬Á´½Ó¿â¼ÓÔØÊ§°Ü¡£", L"×ÖÄ»´íÎó", MB_OK);
		exit(1);
	}
	func_Direct3DCreate9 orig_Direct3DCreate9 = (func_Direct3DCreate9)GetProcAddress(d3d9, "Direct3DCreate9");
	return new Direct3DWrapper(orig_Direct3DCreate9(SDKVersion));
}