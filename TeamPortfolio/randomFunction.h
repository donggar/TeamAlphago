#pragma once
#include "singletonBase.h"
#include <time.h>

class randomFunction : public singletonBase < randomFunction >
{
public:
	randomFunction(void)
	{
		//�и������� �ʴ����� ������ ���ڸ� �޾ƿ�
		srand(GetTickCount());
	}
	~randomFunction(void) {}

	//���� 0 ~ Ư�� ������ �̰��� �Ҷ�
	inline int getInt(int num) { return rand() % num; }

	//������ ������ �ΰ� �ʹ� ��) 10 ~ 20 ���̿� ������ ��
	inline int getFromIntTo(int fromNum, int toNum) { return rand() % (toNum - fromNum + 1) + fromNum; }

};