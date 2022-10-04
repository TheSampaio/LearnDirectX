#include "PCH.h"
#include "Game.h"
#include "Application.h"

// Initialize static pointer reference
Window* Game::m_pWindow = nullptr;

Game::Game()
{
}

Game::~Game()
{
}

// Set an existing window to the game
void Game::SetWindow(Window*& Window)
{
	m_pWindow = Window;
}


// Return a pointer reference to the game's window
Window*& Game::GetWindow()
{
	return m_pWindow;
}
