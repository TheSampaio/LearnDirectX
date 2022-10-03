#ifndef ENGINE_GAME_H
#define ENGINE_GAME_H

#include "Window.h"

class Game
{
public:
	Game();
	virtual ~Game();

	// Pure virtual functions
	virtual void Start()  PURE;
	virtual void Update() PURE;
	virtual void Draw()	  PURE;
	virtual void Finish() PURE;

protected:
	static Window*& GetWindow();

private:
	static Window*& m_pWindow;
};

#endif
