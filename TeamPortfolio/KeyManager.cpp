#include "stdafx.h"
#include "KeyManager.h"

KeyManager::KeyManager()
{
}
KeyManager::~KeyManager()
{
}


HRESULT KeyManager::init(void)
{
	//모든 키에 대해서 처음에 안눌러져있다고 선언
	for (int i = 0; i < KEYMAX; i++)
	{
		//저번에 1번만 했는데 키 입력에 딜레이가 있고 동시에 했을 때 씹히는 상황이 나와서 그냥 2번을 함
		this->getKeyUp().set(i, false);
		this->getKeyUp().set(i, false);
	}
	return S_OK;
}

void KeyManager::release(void)
{
}

bool KeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		//만약 해당키가 눌러져있지 않다면
		if (!this->getKeyDown()[key])
		{
			//눌러졌다고 말해라
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);

	return false;
}

bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) this->setKeyUp(key, true);
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return true;
		}
	}

	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool KeyManager::isTogglekey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	return false;
}
