#include "PCH.h"
#include "Window.h"

// Windows's default main function
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hInstancePrev, _In_ PSTR cmdLine, _In_ int cmdShow)
{
	// Gets window's static reference
	Window& window = Window::GetInstance();

	// Set-up the window
	window.SetTitle("Learn DirectX");
	window.SetSize(1280, 720);

	// Creates the window
	window.Create();

	// Main loop
	do
	{
		// Process window's events
		window.PollEvents();

		// Closes the window with the "Escape" key
		if (window.GetKeyTap(Esc))
			window.Close();

	} while (window.GetMessages().message != WM_QUIT);

	// Returns the application's state to the system
	return static_cast<int>(window.GetMessages().wParam);
}
