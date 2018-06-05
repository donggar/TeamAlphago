#pragma once
#include"singletonBase.h"
#include<bitset>

using namespace std;

//키가 눌러지는 모든 상황 가정했을때 256가지
#define KEYMAX 256

class KeyManager : public singletonBase <KeyManager>
{
private:
	//bitset은 그냥  비트와 같다 0과 1이다 bool 과 같다 키보드 신호가 왔냐 안왔냐만 감지
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
public:
	HRESULT init(void);
	void release(void);

	bool isOnceKeyDown(int key);         //키를 누를때
	bool isOnceKeyUp(int key);			 //키를 땠을때
	bool isStayKeyDown(int key);		 //키를 계속 누를때
	bool isTogglekey(int key);			 //키를 누루면 그상태가 유지되게 한다

	//키에 대한 접근자
	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }

	//키에 대한 설정자
	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }

	KeyManager();
	~KeyManager();

};

