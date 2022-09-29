#include "PCH.h"
#include "Application.h"

#include "Resources.h"

// Windows's main function
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ INT nCmdShow)
{
	// Create application
	Application App;

	// Setup application's window	
	App.GetWindow()->SetSize(1024, 720);
	App.GetWindow()->SetIcon(IDI_ICON);
	App.GetWindow()->SetCursor(IDC_CURSOR);
	App.GetWindow()->SetTitle("Game's Name");
	App.GetWindow()->SetBackgroundColor(219, 244, 255);
	App.GetWindow()->SetDisplayMode(Window::EDisplayMode::Fullscreen);

	// Runs application in a constant loop
	return App.Start();
}