#include "PCH.h"

#include "Application.h"
#include "Resources.h"

// Create main games's class
class MainGame : public Game
{
public:
	// Game's main functions
	void Start();
	void Update();
	void Draw();
	void Finish();

private:
	// Declare game's variables
	bool Button;
};

void MainGame::Start()
{
	// Initialize game's global variable
	Button = false;

	// Feedbacks player
	MessageBox(GetWindow()->GetId(), "The game was started!", "Game", MB_OK | MB_ICONINFORMATION);
}

void MainGame::Update()
{
	// Close window with "Escape" key was pressed and released
	if (GetWindow()->GetKeyPressed(VK_ESCAPE))
	{
		Button = true;
	}

	if (Button)
	{
		if (GetWindow()->GetKeyReleased(VK_ESCAPE))
		{
			Button = false;
			GetWindow()->Close();
		}
	}
}

void MainGame::Draw()
{
}

void MainGame::Finish()
{
	// Feedbacks player
	MessageBox(GetWindow()->GetId(), "The game will be finished.", "Game", MB_OK | MB_ICONINFORMATION);
}

// Windows's main function
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ INT nCmdShow)
{
	// Create application
	Application App;

	// Setup application's window	
	App.GetWindow()->SetSize(1280, 720);
	App.GetWindow()->SetIcon(IDI_ICON);
	App.GetWindow()->SetCursor(IDC_CURSOR);
	App.GetWindow()->SetTitle("Game's Name");
	App.GetWindow()->SetBackgroundColor(255, 253, 186);
	App.GetWindow()->SetDisplayMode(Window::EDisplayMode::Windowed);

	// Runs application in a constant loop
	return App.Start(new MainGame);
}