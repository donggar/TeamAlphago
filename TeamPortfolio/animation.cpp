#include "stdafx.h"
#include "animation.h"


animation::animation() :
	_frameNum(0),
	_frameWidth(0),
	_frameHeight(0),
	_loop(FALSE),
	_frameUpdateSec(0),
	_elapsedSec(0),
	_nowPlayIndex(0),
	_play(FALSE)
{
}


animation::~animation()
{
}

HRESULT animation::init(int totalW, int totalH, int frameW, int frameH)
{
	_frameWidth = frameW;
	_frameHeight = frameH;
	int _frameNumWidth = totalW / _frameWidth;
	int _frameNumHeight = totalH / _frameHeight;

	_frameNum = _frameNumWidth * _frameNumHeight;

	for (int i = 0; i < _frameNumHeight; ++i)
		for (int j = 0; j < _frameNumWidth; ++j)
			_frameList.push_back({ j * _frameWidth, i * _frameHeight });

	setDefPlayFrame();
	return S_OK;
}

void animation::release(void)
{
}

void animation::setDefPlayFrame(BOOL reverse, bool loop)
{
	_loop = loop;
	_playList.clear();
	if (reverse)
		if (_loop) {
			for (int i = 0; i < _frameNum; ++i)
				_playList.push_back(i);
			for (int i = _frameNum - 1; i >= 0; --i)
				_playList.push_back(i);
		}
		else {
			for (int i = 0; i < _frameNum; ++i)
				_playList.push_back(i);
			for (int i = _frameNum - 1; i >= 0; --i)
				_playList.push_back(i);
		}
	else
		if (_loop)
			for (int i = 0; i < _frameNum; ++i)
				_playList.push_back(i);
		else
			for (int i = 0; i < _frameNum; ++i)
				_playList.push_back(i);
}

void animation::setPlayFrame(int * playArr, int arrLen, BOOL loop)
{
	_loop = loop;
	_playList.clear();
	for (int i = 0; i < arrLen; ++i)
		_playList.push_back(playArr[i]);
}

void animation::setPlayFrame(int start, int end, BOOL reverse, BOOL loop)
{
	_loop = loop;
	_playList.clear();
	//프레임 갯수가 1장일 때
	if (start == end)
	{
		_playList.clear();
		stop();
		return;
	}
	if (start > end)
	{
		if (reverse)
		{
			if (_loop)
			{
				for (int i = start; i >= end; --i)
				{
					_playList.push_back(i);
				}
				for (int i = end + 1; i < start; ++i)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; --i)
				{
					_playList.push_back(i);
				}
				for (int i = end + 1; i < start; ++i)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i >= end; --i)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i >= end; --i)
				{
					_playList.push_back(i);
				}
			}
		}
	}
	else
	{
		if (reverse)
		{
			if (_loop)
			{
				for (int i = start; i < end; ++i)   //sdfasdasd
				{
					_playList.push_back(i);
				}
				for (int i = end + 1; i > start; --i) //asdasdasd
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}
				for (int i = end + 1; i > start; --i)
				{
					_playList.push_back(i);
				}
			}
		}
		else
		{
			if (_loop)
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}
			}
			else
			{
				for (int i = start; i < end; ++i)
				{
					_playList.push_back(i);
				}
			}
		}
	}
}

void animation::setFPS(int framePerSec)
{
	_frameUpdateSec = 1.0f / framePerSec;
}

void animation::frameUpdate(float elapsedTime)
{
	if (_play) {
		_elapsedSec += elapsedTime;
		if (_elapsedSec >= _frameUpdateSec) {
			_elapsedSec -= _frameUpdateSec;
			_nowPlayIndex++;
			if (_nowPlayIndex == _playList.size()) {
				if (_loop) _nowPlayIndex = 0;
				else {
					_nowPlayIndex--;
					_play = FALSE;
				}
			}
		}
	}
}

void animation::start(void)
{
	_play = TRUE;
	_nowPlayIndex = 0;
}

void animation::stop(void)
{
	_play = FALSE;
	_nowPlayIndex = 0;
}

void animation::pause(void)
{
	_play = FALSE;
}

void animation::resume(void)
{
	_play = TRUE;
}
