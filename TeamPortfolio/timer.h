#pragma once
class timer
{
private:
	bool _isHardware;
	float _timeScale;
	float _timeElapsed;

	//__int64 = 8 byte integer
	//unsigned long = 4 byte integer
	__int64 _currentTime;
	__int64 _lastTime;
	__int64 _periodFrequency;

	unsigned long _framerate;
	unsigned long _FPSframeCount;

	float _FPSTimeElapsed;
	float _worldTime;
public:
	timer();
	~timer();

	HRESULT init(void);
	void tick(float lockFPS = 0.0f);
	unsigned long getFramerate(char* str = NULL) const;

	inline float getElapsedTime(void) const { return _timeElapsed; }
	inline float getWorldTime(void) const { return _worldTime; }
};