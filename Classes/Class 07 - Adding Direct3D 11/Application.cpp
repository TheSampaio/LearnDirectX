#include "PCH.h"
#include "Application.h"

// Initialize window's static pointers
Game* Application::m_pGame = nullptr;
Graphics* Application::m_pGraphics = nullptr;
Window* Application::m_pWindow = nullptr;

// Alocate memory
Application::Application()
{
	m_pGraphics = new Graphics;
	m_pWindow = new Window;
}

// Delete alocated memory
Application::~Application()
{
	delete m_pGame;
	delete m_pGraphics;
	delete m_pWindow;
}

// Start the application
int Application::Start(Game* Level)
{
	m_pGame = Level;
	m_pGame->SetWindow(m_pWindow);

	// Create window and verify if was succeed
	if (!m_pWindow->Create())
	{
		MessageBox(NULL, "Failed to create window.", "Application", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	// Create renderer and verify if was succeed
	if (!m_pGraphics->Initialize(m_pWindow))
	{
		MessageBox(NULL, "Failed to initialize renderer.", "Application", MB_OK | MB_ICONERROR);
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

	// Starts the game
	m_pGame->Start();

	// === Main Loop (Gameloop)
	do
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			// Process all window's messages
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		else
		{
			// Updates game and clears back buffer
			m_pGame->Update();
			m_pGraphics->ClearBuffer();
			
			// Draws at back buffer and show it
			m_pGame->Draw();
			m_pGraphics->PresentBuffer();

			// """V-Sync"""
			Sleep(1);
		}
	} while (Message.message != WM_QUIT);

	// Finishes the game
	m_pGame->Finish();
	return static_cast<int>(Message.wParam);
}
