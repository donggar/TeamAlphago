#pragma once

template <typename T>
class singletonBase
{
protected:
	//�̱����̶� ���� ����ϴ� ���� �޸𸮿� ���ֽ��� ��� ��ü������ ������ �� �� �ְ� �ϴ� ������ �����̴�
	
	//static�� �ڷ����� ����ȭ �����ְ�, ���ø� �����ͱ� ������ � ���̵� ����ų���ִ�
	static T* singleton;

	singletonBase() {};
	~singletonBase() {};
public:

	//�̱��� ������
	static T* getSingleton(void);
	//�̱��� ���� �Լ�
	void releaseSingleton(void);
	
};

//�̱��� �ʱ�ȭ
template <typename T>
T* singletonBase<T>::singleton = 0;

template <typename T>
T* singletonBase<T>::getSingleton()
{
	//���࿡ �̱���ȭ�� �Ǿ����� �ʴٸ� �̱��� ȭ(���ø� �����Ҵ�) ���Ѷ�
	if (!singleton) singleton = new T;

	//�׸��� ��ȯ
	return singleton;
}


//�̱��� ���� �Լ�
template <typename T>
void singletonBase<T>::releaseSingleton(void)
{
	//�̱����� �ִٸ�
	if (singleton)
	{
		//�����Ҵ��߱⶧���� �޸𸮿��� �������Ѷ�
		delete singleton;

		singleton = 0;
	}
}