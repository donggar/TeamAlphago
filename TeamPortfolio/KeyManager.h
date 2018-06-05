#pragma once
#include"singletonBase.h"
#include<bitset>

using namespace std;

//Ű�� �������� ��� ��Ȳ ���������� 256����
#define KEYMAX 256

class KeyManager : public singletonBase <KeyManager>
{
private:
	//bitset�� �׳�  ��Ʈ�� ���� 0�� 1�̴� bool �� ���� Ű���� ��ȣ�� �Գ� �ȿԳĸ� ����
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
public:
	HRESULT init(void);
	void release(void);

	bool isOnceKeyDown(int key);         //Ű�� ������
	bool isOnceKeyUp(int key);			 //Ű�� ������
	bool isStayKeyDown(int key);		 //Ű�� ��� ������
	bool isTogglekey(int key);			 //Ű�� ����� �׻��°� �����ǰ� �Ѵ�

	//Ű�� ���� ������
	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }

	//Ű�� ���� ������
	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

	KeyManager();
	~KeyManager();

};

