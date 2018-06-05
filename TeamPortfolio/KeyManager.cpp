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
	//��� Ű�� ���ؼ� ó���� �ȴ������ִٰ� ����
	for (int i = 0; i < KEYMAX; i++)
	{
		//������ 1���� �ߴµ� Ű �Է¿� �����̰� �ְ� ���ÿ� ���� �� ������ ��Ȳ�� ���ͼ� �׳� 2���� ��
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
		//���� �ش�Ű�� ���������� �ʴٸ�
		if (!this->getKeyDown()[key])
		{
			//�������ٰ� ���ض�
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
