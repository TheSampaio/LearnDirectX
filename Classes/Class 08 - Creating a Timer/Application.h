#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include "Game.h"
#include "Graphics.h"
#include "Timer.h"
#include "Window.h"

class CApplication
{
public:
	static SGame* Game;
	static RGraphics* Graphics;
	static CWindow* Window;
	static float DeltaTime;

	CApplication();
	~CApplication();

	// === Main Methods ===
	static void Pause();
	static void Resume();

	int Start(SGame* Level);

private:
	static ITimer m_Timer;
	static bool m_Paused;

	float ProcessFrameTime();
	int Update();
};

#endif
