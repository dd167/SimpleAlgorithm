#pragma once
#include <time.h>
#include <stdlib.h>

class Clock
{
public:
	void start()
	{
		_start = clock();	
	}

	void stop()
	{
		_finish = clock();
	}

	double duration()
	{
		return (double)(_finish - _start) / CLOCKS_PER_SEC;
	}

private:
	clock_t _start, _finish;
};