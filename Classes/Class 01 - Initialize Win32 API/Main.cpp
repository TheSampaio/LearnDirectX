// Get ONLY Windows 32 bits or major (Exclude 16 bits functions)
#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN

	// Include "Windows" and "Windows Extended" APIs
	#include <windows.h>
	#include <windowsx.h>
#endif

// Windows's main function
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ int nCmdShow)
{
	// Create simple message box
	MessageBox(NULL, "Hello World!", "Win32 API", MB_OK | MB_ICONINFORMATION);
	return 0;
}