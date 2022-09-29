// Get ONLY Windows 32 bits or major (Exclude 16 bits functions)
#ifndef WIN32_MEAN_AND_LEAN
#define WIN32_MEAN_AND_LEAN

	// Include "Windows" and "Windows Extended" APIs
	#include <windows.h>
	#include <windowsx.h>
#endif

// Store all keyboard's keys
static bool WindowKeys[256]{ false };

// Window's procedure function
LRESULT CALLBACK Procedure(HWND hWindow, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	// If a keyboard's key was pressed
	case WM_KEYDOWN:
		WindowKeys[wParam] = true;
		MessageBox(hWindow, "You pressed a keyboard's key.", "Input Detected", MB_OK | MB_ICONINFORMATION);
		return 0;

	// If a keyboard's key was released
	case WM_KEYUP:
		WindowKeys[wParam] = false;
		return 0;

	// If window was closed
	case WM_CLOSE:

		// Ask if user want to close the window
		if (MessageBox(hWindow, "Do you really want to close the window?", "Warning", MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING) == IDYES)
		{
			PostQuitMessage(NULL);
			return 0;
		}

		else
		{
			return 0;
		}

	default:
		return DefWindowProc(hWindow, Message, wParam, lParam);
	}
}

// Windows's main function
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ int nCmdShow)
{
	// Screen's properties
	unsigned int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	unsigned int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	
	// Window's properties
	HWND hWindow {NULL};
	WNDCLASSEX WindowClass {NULL};
	const char* WindowClassName = "BasicWindow";
	const char* WindowTitle = "Window";
	unsigned int WindowWidth = 800;
	unsigned int WindowHeight = 600;

	// Store window's messages
	MSG Message{ NULL };

	// Setup window's class
	WindowClass.cbSize = sizeof(WindowClass);
	WindowClass.lpfnWndProc = Procedure;
	WindowClass.cbClsExtra = NULL;
	WindowClass.cbWndExtra = NULL;
	WindowClass.hbrBackground = static_cast<HBRUSH>(CreateSolidBrush(RGB(0, 0, 0)));
	WindowClass.hInstance = hInstance;
	WindowClass.lpszClassName = WindowClassName;

	// Register window's class
	if (!RegisterClassEx(&WindowClass))
	{
		MessageBox(hWindow, "Failed to register window class!", "Error", MB_OK | MB_ICONERROR);
	}

	// Create window
	hWindow = CreateWindowEx
	(
		NULL,
		WindowClassName,
		WindowTitle,
		WS_OVERLAPPED | WS_SYSMENU,
		((ScreenWidth / 2) - (WindowWidth / 2)), ((ScreenHeight / 2) - (WindowHeight / 2)),
		WindowWidth, WindowHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	// Show created window
	ShowWindow(hWindow, SW_SHOW);

	// Process window's messages
	while (GetMessage(&Message, NULL, NULL, NULL))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return static_cast<int>(Message.wParam);
}