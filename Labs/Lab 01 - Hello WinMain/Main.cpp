// Include Windows API (Without 16 bits source code)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

// Windows's default main function
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ PSTR cmdLine, _In_ int cmdShow)
{
	// Creates a custom message box
	MessageBox(nullptr, L"Hello World!", L"Win 32 API", MB_OK | MB_ICONINFORMATION);
	return 0;
}
