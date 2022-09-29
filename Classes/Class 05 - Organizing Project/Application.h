#pragma once

#include "PCH.h"
#include "Window.h"

class Application
{
public:
	Application();
	~Application();

	// === Main Methods ===
	int Start();
	Window* GetWindow();

private:
	static Window* m_pWindow;

	int Update();
};

