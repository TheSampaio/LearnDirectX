#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include "Game.h"
#include "Graphics.h"
#include "Window.h"

class Application
{
public:
	Application();
	~Application();

	// === Main Methods ===
	Window* GetWindow();
	int Start(Game* Level);

private:
	static Game* m_pGame;
	static Graphics* m_pGraphics;
	static Window* m_pWindow;

	int Update();
};

#endif
