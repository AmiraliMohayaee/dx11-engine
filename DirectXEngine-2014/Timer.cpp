#include "Timer.h"
#include <cstdlib>
#include <Windows.h>


namespace DXEngine
{
	Timer::Timer():
		m_dt(0.0),
		m_stopped(true),	
		m_baseTime(0),	
		m_pausedTime(0),	
		m_stopTime(0),	
		m_prevTime(0),	
		m_currentTime(0),
		m_secondsPerCount(0.0)
		{
			// Making sure that the time is counted in milliseconds in floating points
			// ie: one second is 1.0 and half a second is 0.5 as in 500 milliseconds
			__int64 countsPerSecond;
			QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecond);	// Tells us that there are a 1000 ticks a second (usually)
			m_secondsPerCount = 1.0 / (double)countsPerSecond;
		}


	float Timer::GetDt() const
	{
		return m_dt;
	}


	void Timer::Start()
	{
		if(m_stopped)
		{
			__int64 startTime;
			QueryPerformanceFrequency((LARGE_INTEGER*)&startTime);

			// When the application is actually kicked off, there is some time missed
			// before the timer is initiated, so this adds the missed time to the paused
			// time, therefor ignored.
			m_pausedTime += startTime - m_stopTime;	

			m_prevTime = startTime;
			m_stopTime = 0;

			m_stopped = false;
		}
	}


	// Makes sure that the total elapsed time after pause is counted
	// so that there aren't any leaks in counting
	void Timer::Reset()
	{
		__int64 currentTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

		m_baseTime = m_prevTime = currentTime;
		m_stopTime = 0;

		m_stopped = false;
	}

	// Pauses the timer
	void Timer::Stop()
	{
		if (!m_stopped)
		{
			__int64 currentTime;
			QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
			m_stopTime = currentTime;

			m_stopped = true;
		}
	}

	void Timer::Update()
	{
		if(m_stopped)
		{
			m_dt = 0.0;
			return;
		}

		QueryPerformanceCounter((LARGE_INTEGER*)&m_currentTime);

		m_dt = (float)((m_currentTime - m_prevTime) * m_secondsPerCount);	// Everything is cast to float

		m_prevTime = m_currentTime;

		m_dt = (float)(m_dt < 0.0 ? 0.0 : m_dt);	// Make sure dt is not less than 0
	}

	// Checks the total running time of the applications outside of pause time
	float Timer::GetTotalTime() const
	{
		if(m_stopped)
			return (float) (((m_stopTime - m_pausedTime) - m_baseTime) * m_secondsPerCount);

		else
			return (float) (((m_currentTime - m_pausedTime) - m_baseTime) * m_secondsPerCount);
	}

	
	// Checks the duration time for how long a function of type void and returns a float
	// which represents the time passed in seconds
	// Mostly for debug situations
	float Timer::GetDuration(std::function <void(void)> func)
	{
		__int64 startTime, endTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&startTime);

		func();

		QueryPerformanceCounter((LARGE_INTEGER*)&endTime);

		return (float)((endTime - startTime) * m_secondsPerCount);
	}


	/* Example of the GetDuration decleration:
		float duration = DXEngine::TheTimer::Instance() -> GetDuration( [] ()
		{
			//function here
		} );
	*/
}