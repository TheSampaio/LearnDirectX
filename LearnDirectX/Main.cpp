// Don't include Windows's 16 Bits functions
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

#include "Resource.h"

// Screen's width and height
int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

// Window's properties
int WindowWidth = 1024;
int WindowHeight = 720;
int WindowStyle = WS_OVERLAPPED | WS_SYSMENU;
bool bWindowFullscreen = false;
bool WindowKeys[256] {0};

// Define window class
HWND hWindow{ NULL };

// Window's procedure prototype
LRESULT CALLBACK Procedure(HWND, UINT, WPARAM, LPARAM);

// Run ONCE on game starts
void GameStart()
{
}

// Run EVERY FRAME after game starts
void GameUpdate()
{
	if (WindowKeys[VK_ESCAPE]){ PostMessage(hWindow, WM_DESTROY, 0, 0); }
}

// Draw everithing that we need
void GameDraw()
{
}

// Run ONCE ater game update
void GameEnd()
{
}

// Windows's main function
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{	
	MSG Message{ NULL };
	WNDCLASSEX Window{ NULL };
	const char* WindowClassName = "BasicWindow";

	// Setup window class
	Window.cbSize = sizeof(Window);
	Window.style = CS_HREDRAW | CS_VREDRAW;
	Window.lpfnWndProc = Procedure;
	Window.cbClsExtra = 0;
	Window.cbWndExtra = 0;
	Window.hInstance = hInstance;
	Window.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
	Window.hIconSm = NULL;
	Window.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR));
	Window.hbrBackground = static_cast<HBRUSH>(CreateSolidBrush(RGB(0, 0, 0)));
	Window.lpszMenuName = NULL;
	Window.lpszClassName = WindowClassName;

	// Register window class
	if (!RegisterClassEx(&Window))
	{
		MessageBox(hWindow, "Failed to register window.", "Error!", MB_OK | MB_ICONERROR);
		return -1;
	}

	if (bWindowFullscreen)
	{
		// Window's width and height
		WindowWidth = ScreenWidth;
		WindowHeight = ScreenHeight;
		WindowStyle = WS_POPUP;
	}

	// Create window's instance
	hWindow = CreateWindowEx
	(
		NULL,																					// Window's extended styles
		WindowClassName,																		// Window's class name
		"Window",																				// Window's title
		WindowStyle,																			// Window's standard styles
		((ScreenWidth / 2) - (WindowWidth / 2)), ((ScreenHeight / 2) - (WindowHeight / 2)),		// Window's position
		WindowWidth, WindowHeight,																// Window's size
		NULL,
		NULL,
		hInstance,
		NULL
	);	

	if (!bWindowFullscreen)
	{
		// Rect with client area
		RECT WindowRect{ 0, 0, WindowWidth, WindowHeight };

		// Adjust window's size to screen
		AdjustWindowRectEx(&WindowRect, GetWindowStyle(hWindow), (GetMenu) != NULL, GetWindowExStyle(hWindow));

		// Update window's position on screen
		int WindowPositionX = (ScreenWidth / 2)  - (WindowRect.right - WindowRect.left) / 2;
		int WindowPositionY = (ScreenHeight / 2) - (WindowRect.bottom - WindowRect.top) / 2;

		// Resize window and position it on the new screen's location
		MoveWindow(hWindow, WindowPositionX, WindowPositionY, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, true);
	}

	// Show and update window
	ShowWindow(hWindow, SW_SHOW);
	UpdateWindow(hWindow);

	// Call GameStart
	GameStart();

	// Game's main loop (Gameloop)
	do
	{
		// Get window's messages
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		else
		{
			GameUpdate();
			GameDraw();
		}
	}
	while (Message.message != WM_QUIT);

	// Terminate game
	GameEnd();

	// Return the window's procedure's code message
	return static_cast<int>(Message.wParam);
}

// Window's procedure
LRESULT CALLBACK Procedure(HWND hWindow, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
		// Process all keydown events
		case WM_KEYDOWN:
			WindowKeys[wParam] = true;
			return 0;

		// Process all keyup events
		case WM_KEYUP:
			WindowKeys[wParam] = false;
			return 0;

		// Process destroy window event
		case WM_DESTROY:
			PostQuitMessage(NULL);
			return 0;
	}

	return DefWindowProc(hWindow, Message, wParam, lParam);
}