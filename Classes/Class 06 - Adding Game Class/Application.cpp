#include "PCH.h"
#include "Application.h"

// Initialize window's static pointers
Game* Application::m_pGame = nullptr;
Window* Application::m_pWindow = nullptr;

Application::Application()
{
	m_pWindow = new Window;
}

Application::~Application()
{
	delete m_pGame;
	delete m_pWindow;
}

// Start the application
int Application::Start(Game* Level)
{
	m_pGame = Level;

	// Create window and verify if was succeed
	if (!m_pWindow->Create())
	{
		MessageBox(NULL, "Failed to create window.", "Application", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	// Runs the application
	return Update();
}

// Returns current window
Window* Application::GetWindow()
{
	return m_pWindow;
}

// Runs the application
int Application::Update()
{
	MSG Message{ NULL };

	m_pGame->Start();

	// === Main Loop (Gameloop)
	do
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		else
		{
			m_pGame->Update();
			// TODO: Renderer->Clear();
			
			m_pGame->Draw();
			// TODO: Renderer->Show();

			// """V-Sync"""
			Sleep(16);
		}
	} while (Message.message != WM_QUIT);

	m_pGame->Finish();

	return static_cast<int>(Message.wParam);
}
