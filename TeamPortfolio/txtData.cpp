#include "stdafx.h"
#include "txtData.h"

txtData::txtData(){}

txtData::~txtData(){}

HRESULT txtData::init(){ return S_OK; }

void txtData::release(){}

//save
void txtData::txtSave(const char * saveFileName, vector<string> vStr)
{
	HANDLE file;

	char str[128];
	DWORD write;
	strncpy_s(str, 128, vectorArrayCombine(vStr), 126);
	file = CreateFile(
		saveFileName,             //파일이름
		GENERIC_WRITE,			  //쓰기 권환
		FALSE,					  //공유 모드
		NULL,					  //상속자에게 값을 넘길거 있는가
		CREATE_ALWAYS,			  //항상 새로운파일 만든다.
		FILE_ATTRIBUTE_NORMAL,	  //모든 속성(읽기 전용, 숨긴, 운영제제 전용파일)을 지정하지 않는다.
		NULL					  //생성된 템플릿 파일의 유효한 핸들에 속성을 넣는 BOOL값
	);
	//strlen 등 문자열 길이 함수를 쓰면 먹통된다
	WriteFile(      
		file, 		//대상 파일으 핸들
		str, 		//데이터가 들어있는 버퍼
		128, 		//쓰고자 하는 바이트 수
		&write,		//쓰고자 하는 바이트 수를 리턴하기 위한 DWORD변수의 포인터
		NULL);		//비동기입출력을 할 때 사용 BOOL값

	CloseHandle(file);
	/*
	열려진 핸들을 닫는다.(버퍼, 프로세스, 파일)
	WIN32에서 핸들로 표현되는 모든 것을 말한다.
	그러나 아이콘 , 팬, 브러쉬 GDI오브젝튼 닫을 수 없다.
	*/
}

char * txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[128];

	ZeroMemory(str, sizeof(str));
	//X Axis, Y Axis, CurrentHP, MaxHP
	//100, 100, 100, 100
	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, 128, vArray[i].c_str(), 126);
		if (i + 1 < vArray.size()) strcat(str, ",");
	}
	return str;
}

vector<string> txtData::txtLoad(const char * loadFileName)
{
	HANDLE file;
	char str[128];
	DWORD read;

	file = CreateFile(
		loadFileName,
		GENERIC_READ,          //쓰기 
		FALSE,
		NULL,
		OPEN_EXISTING,         //파일이 존재할 경우에만 파일을 연다.
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	ReadFile(file, str, 128, &read, NULL);
	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	const char* separator = ",";
	char* token;

	token = strtok(charArray, separator);
	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}
	return vArray;
}
