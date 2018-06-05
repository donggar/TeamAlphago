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
		saveFileName,             //�����̸�
		GENERIC_WRITE,			  //���� ��ȯ
		FALSE,					  //���� ���
		NULL,					  //����ڿ��� ���� �ѱ�� �ִ°�
		CREATE_ALWAYS,			  //�׻� ���ο����� �����.
		FILE_ATTRIBUTE_NORMAL,	  //��� �Ӽ�(�б� ����, ����, ����� ��������)�� �������� �ʴ´�.
		NULL					  //������ ���ø� ������ ��ȿ�� �ڵ鿡 �Ӽ��� �ִ� BOOL��
	);
	//strlen �� ���ڿ� ���� �Լ��� ���� ����ȴ�
	WriteFile(      
		file, 		//��� ������ �ڵ�
		str, 		//�����Ͱ� ����ִ� ����
		128, 		//������ �ϴ� ����Ʈ ��
		&write,		//������ �ϴ� ����Ʈ ���� �����ϱ� ���� DWORD������ ������
		NULL);		//�񵿱�������� �� �� ��� BOOL��

	CloseHandle(file);
	/*
	������ �ڵ��� �ݴ´�.(����, ���μ���, ����)
	WIN32���� �ڵ�� ǥ���Ǵ� ��� ���� ���Ѵ�.
	�׷��� ������ , ��, �귯�� GDI������ư ���� �� ����.
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
		GENERIC_READ,          //���� 
		FALSE,
		NULL,
		OPEN_EXISTING,         //������ ������ ��쿡�� ������ ����.
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
