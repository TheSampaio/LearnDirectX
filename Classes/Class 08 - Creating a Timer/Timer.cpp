#include "PCH.h"
#include "Timer.h"

ITimer::ITimer()
{
	// Gets frequency
	QueryPerformanceFrequency(&m_Frequency);

	// Sets m_Start and m_End to zero
	ZeroMemory(&m_Start, sizeof(m_Start));
	ZeroMemory(&m_End, sizeof(m_End));

	m_Paused = false;
}

// Starts timer
void ITimer::Start()
{
	if (m_Paused)
	{
		long long ElapsedTime = m_End.QuadPart - m_Start.QuadPart;

		QueryPerformanceCounter(&m_Start);

		m_Start.QuadPart -= ElapsedTime;
		m_Paused = false;
	}

	else
	{
		QueryPerformanceCounter(&m_Start);
	}
}

// Pauses timer
void ITimer::Pause()
{
	if (!m_Paused)
	{
		QueryPerformanceCounter(&m_End);
		m_Paused = true;
	}
}

// Resets timer
float ITimer::Reset()
{
	long long ElapsedTime = 0;

	if (m_Paused)
	{
		ElapsedTime = m_End.QuadPart - m_Start.QuadPart;

		QueryPerformanceCounter(&m_Start);

		m_Paused = false;
	}

	else
	{
		QueryPerformanceCounter(&m_End);

		ElapsedTime = m_End.QuadPart - m_Start.QuadPart;

		m_Start = m_End;
	}

	return static_cast<float>(ElapsedTime / static_cast<double>(m_Frequency.QuadPart));
}

// Gets elapsed time timer
float ITimer::GetElapsedTime()
{
	long long ElapsedTime;

	if (m_Paused)
	{
		ElapsedTime = m_End.QuadPart - m_Start.QuadPart;
	}

	else
	{
		QueryPerformanceCounter(&m_End);

		ElapsedTime = m_End.QuadPart - m_Start.QuadPart;
	}

	return static_cast<float>(ElapsedTime / static_cast<double>(m_Frequency.QuadPart));
}
