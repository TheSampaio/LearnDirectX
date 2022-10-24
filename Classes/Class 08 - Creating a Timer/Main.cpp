#include "PCH.h"
#include "Application.h"
#include "Resources.h"

using namespace EngineTypes;

// Create main games's class
class SMainGame : public SGame
{
public:
	// Game's main functions
	void Start();
	void Update();
	void Draw();
	void Finish();

private:
	// Declare game's variables
	Bool Button = false;
};

// Starts EVERYTHING in the game
void SMainGame::Start()
{
	// Initialize game's global variable
}

// Updates EVERYTHING in the game
void SMainGame::Update()
{
	// Close window with "Escape" key was pressed and released
	if (Window->GetKeyPressed(VK_ESCAPE))
	{
		Button = true;
	}

	if (Button)
	{
		if (Window->GetKeyReleased(VK_ESCAPE))
		{
			Button = false;
			Window->Close();
		}
	}
}

// Dras EVERYTHING in the game
void SMainGame::Draw()
{
}

// Destroys EVERYTHING in the game
void SMainGame::Finish()
{
}

// Windows's main function
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdLine, _In_ INT nCmdShow)
{
	// Create application
	CApplication Application;

	// Setup application's window	
	Application.Window->SetSize(1280, 720);
	Application.Window->SetIcon(IDI_ICON);
	Application.Window->SetCursor(IDC_CURSOR);
	Application.Window->SetTitle("Super Game");
	Application.Window->SetBackgroundColor(255, 253, 186);
	Application.Window->SetDisplayMode(Application.Window->EDisplayMode::WINDOWED);
	
	// Enables vertical synchronization
	Application.Graphics->SetVerticalSynchronization(true);

	// Runs application in a constant loop
	return Application.Start(new SMainGame);
}