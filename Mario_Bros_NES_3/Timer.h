#pragma once
#include <time.h>
#include <Windows.h>

class CTimer
{
private:
	static CTimer* _instance;

	ULONGLONG current_time;

public:
	CTimer() { current_time = 0; }

	static CTimer* GetInstance()
	{
		if (_instance == NULL)
			_instance = new CTimer();
		return _instance;
	}

	void InitTime() { current_time = 300000; }

	void Update(DWORD dt)
	{
		current_time -= dt;
		if (current_time <= 0)
			current_time = 0;
	}

	ULONGLONG Get_CurrentTime() { return current_time; }

	int IsTimeOver() { return current_time == 0; }
};
