#ifndef TIMER_H
#define TIMER_H

#include "Singleton.h"
#include <functional>


namespace DXEngine
{
	class Timer : public NonCopyable
	{
	private:
		Timer();
		friend class Singleton <Timer>;

		bool m_stopped;	// Is paused? flag
		__int64 m_baseTime;	//total time elapsed since restart/start
		__int64 m_pausedTime;	//total time paused
		__int64 m_stopTime;	//time last stopped
		__int64 m_prevTime;	//time at last frame 
		__int64 m_currentTime;	//time at this frame

		double m_secondsPerCount;	// Acts like Ticks
		float m_dt;	// Delta Time, if that wasn't obvious

	public:
		float GetDt() const;
		float GetTotalTime() const;

		void Reset();
		void Start();
		void Update();
		void Stop();

		float GetDuration(std::function <void(void)> func);

	};

	typedef Singleton<Timer> TheTimer;
}

#endif