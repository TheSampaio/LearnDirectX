#include "PCH.h"
#include "Application.h"

// Initialize window's static pointers
SGame*		CApplication::Game = nullptr;
RGraphics*	CApplication::Graphics = nullptr;
CWindow*	CApplication::Window = nullptr;
float		CApplication::DeltaTime = 0.0f;

ITimer	CApplication::m_Timer;
bool	CApplication::m_Paused = false;

// Alocate memory
CApplication::CApplication()
{
	Graphics = new RGraphics;
	Window = new CWindow;
}

// Delete alocated memory
CApplication::~CApplication()
{
	delete Game;
	delete Graphics;
	delete Window;
}

void CApplication::Pause()
{
	m_Paused = true;
	m_Timer.Pause();
}

void CApplication::Resume()
{
	m_Paused = false;
	m_Timer.Start();
}

// Start the application
int CApplication::Start(SGame* Level)
{
	Game = Level;

	// Create window and verify if was succeed
	if (!Window->Create())
	{
		MessageBox(NULL, "Failed to create window.", "Application", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	// Initialize graohics and verify if was succeed
	if (!Graphics->Initialize(Window))
	{
		MessageBox(NULL, "Failed to initialize graphics.", "Application", MB_OK | MB_ICONERROR);
		return EXIT_FAILURE;
	}

	timeBeginPeriod(1);
	int ExitCode = Update(); // Runs the application
	timeEndPeriod(1);
	
	return ExitCode;
}

// Runs the application
int CApplication::Update()
{
	MSG Message{ NULL };
	bool PauseControl = true;

	// Starts the game
	m_Timer.Start();
	Game->Start();

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

			if (PauseControl)
			{
				if (Window->GetKeyPressed(VK_PAUSE))
				{
					m_Paused = !m_Paused;
					PauseControl = false;

					if (m_Paused) { m_Timer.Pause(); }
					else { m_Timer.Start(); }
				}
			}

			else
			{
				if (Window->GetKeyReleased(VK_PAUSE))
					PauseControl = true;
			}
		}

		if (!m_Paused)
		{
			DeltaTime = ProcessFrameTime();

			// Updates game and clears back buffer
			Game->Update();
			Graphics->ClearBuffer();
			
			// Draws at back buffer and show it
			Game->Draw();
			Graphics->PresentBuffer();
		}

		else
		{
			Game->OnPause();
		}

	} while (Message.message != WM_QUIT);

	// Finishes the game
	Game->Finish();
	return static_cast<int>(Message.wParam);
}

float CApplication::ProcessFrameTime()
{
#ifdef _DEBUG
	static float TotalTime = 0.0f;
	static unsigned int FrameCount = 0;
#endif
	DeltaTime = m_Timer.Reset();

#ifdef _DEBUG
	TotalTime += DeltaTime;
	FrameCount++;

	if (TotalTime >= 1.0f)
	{
		std::stringstream Text;
		Text << std::fixed;
		Text.precision(1);
		Text << Window->GetTitle().c_str() << " | " << "FPS: " << FrameCount << " | " << "MS: " << DeltaTime * 1000;

		SetWindowText(Window->GetId(), Text.str().c_str());

		FrameCount = 0;
		TotalTime -= 1.0f;
	}
#endif

	return DeltaTime;
}