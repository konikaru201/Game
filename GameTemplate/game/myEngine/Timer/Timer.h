#pragma once

class Timer {
	Timer()
	{
	}
	~Timer()
	{
	}
public:
	static float GetFrameDeltaTime()
	{
		return m_frameDeltaTime;
	}
private:
	static float m_frameDeltaTime;
};