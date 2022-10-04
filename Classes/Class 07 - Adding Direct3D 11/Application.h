#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include "Game.h"
#include "Renderer.h"
#include "Window.h"

class Application
{
public:
	static Window* m_pWindow;

	Application();
	~Application();

	// === Main Methods ===
	int Start(Game* Level);
	Window* GetWindow();

private:
	static Game* m_pGame;
	static Renderer* m_pRenderer;

	int Update();
};

#endif
