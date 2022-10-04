#include "PCH.h"
#include "Game.h"
#include "Application.h"

// Initialize static pointer reference
Window*& Game::m_pWindow = Application::m_pWindow;

Game::Game()
{
}

Game::~Game()
{
}

// Return a pointer reference to the game's window
Window*& Game::GetWindow()
{
	return m_pWindow;
}
