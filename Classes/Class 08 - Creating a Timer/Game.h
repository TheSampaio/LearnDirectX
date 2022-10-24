#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H

#include "Window.h"

class SGame
{
public:
	SGame();
	virtual ~SGame();

	virtual void OnPause();

	// Pure virtual functions
	virtual void Start()  PURE;
	virtual void Update() PURE;
	virtual void Draw()   PURE;
	virtual void Finish() PURE;

protected:
	static CWindow*& Window;
};

#endif
