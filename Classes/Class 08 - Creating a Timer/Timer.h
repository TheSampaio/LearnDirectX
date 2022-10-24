#ifndef ENGINE_TIMER_H
#define ENGINE_TIMER_H

class ITimer
{
public:
	ITimer();

	void Start();
	void Pause();
	float Reset();
	float GetElapsedTime();

private:
	LARGE_INTEGER m_Start, m_End, m_Frequency;
	bool m_Paused;
};

#endif
