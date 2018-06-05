#pragma once
#include "singletonBase.h"
#include <time.h>

class randomFunction : public singletonBase < randomFunction >
{
public:
	randomFunction(void)
	{
		//밀리세컨드 초단위로 랜덤한 숫자를 받아옴
		srand(GetTickCount());
	}
	~randomFunction(void) {}

	//내가 0 ~ 특정 난수를 뽑고자 할때
	inline int getInt(int num) { return rand() % num; }

	//난수의 구간을 두고 싶다 예) 10 ~ 20 사이에 랜덤한 수
	inline int getFromIntTo(int fromNum, int toNum) { return rand() % (toNum - fromNum + 1) + fromNum; }

};