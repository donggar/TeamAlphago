#pragma once

template <typename T>
class singletonBase
{
protected:
	//싱글톤이란 자주 사용하는 것을 메모리에 상주시켜 어느 객체에서든 접근이 될 수 있게 하는 디자인 패턴이다
	
	//static은 자료형을 전역화 시켜주고, 템플릿 포인터기 때문에 어떤 것이든 가르킬수있다
	static T* singleton;

	singletonBase() {};
	~singletonBase() {};
public:

	//싱글톤 접근자
	static T* getSingleton(void);
	//싱글톤 해제 함수
	void releaseSingleton(void);
	
};

//싱글톤 초기화
template <typename T>
T* singletonBase<T>::singleton = 0;

template <typename T>
T* singletonBase<T>::getSingleton()
{
	//만약에 싱글톤화가 되어있지 않다면 싱글톤 화(템플릿 동적할당) 시켜라
	if (!singleton) singleton = new T;

	//그리고 반환
	return singleton;
}


//싱글톤 해제 함수
template <typename T>
void singletonBase<T>::releaseSingleton(void)
{
	//싱글톤이 있다면
	if (singleton)
	{
		//동적할당했기때문에 메모리에서 해제시켜라
		delete singleton;

		singleton = 0;
	}
}