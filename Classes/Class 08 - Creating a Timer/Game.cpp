#include "PCH.h"
#include "Game.h"
#include "Application.h"

// Initialize static pointer reference
CWindow*& SGame::Window = CApplication::Window;

SGame::SGame()
{
}

SGame::~SGame()
{
}

void SGame::OnPause()
{
	Sleep(10);
}
