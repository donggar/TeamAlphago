#include "stdafx.h"
#include "timer.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

timer::timer()
{
}


timer::~timer()
{
}

HRESULT timer::init(void)
{
	//Querry Performance Frequency = high performance timer function
	//LARGE_INTEGER = exceeds 32 bit limitations
	//returns current CPU response time
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency)) {
		_isHardware = true;
		//assign _lastTime
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
		_timeScale = 1.0f / _periodFrequency;
	}
	else {
		_isHardware = false;
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}
	_framerate = 0;
	_FPSframeCount = 0;
	_FPSTimeElapsed = 0;
	_worldTime = 0;
	return S_OK;
}

void timer::tick(float lockFPS)
{
	if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_currentTime);
	else _currentTime = timeGetTime();
	_timeElapsed = (_currentTime - _lastTime) * _timeScale;
	if (lockFPS > 0.0f) {
		while (_timeElapsed < 1.0f / lockFPS) {
			if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_currentTime);
			else _currentTime = timeGetTime();

			_timeElapsed = (_currentTime - _lastTime) * _timeScale;
		}
	}
	_lastTime = _currentTime;
	_FPSframeCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;
	if (_FPSTimeElapsed > 1.0f) {
		_framerate = _FPSframeCount;
		_FPSframeCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

unsigned long timer::getFramerate(char * str) const
{
	if (str != NULL) {
		wsprintf(str, "FPS: %d", _framerate);
	}
	return _framerate;
}
