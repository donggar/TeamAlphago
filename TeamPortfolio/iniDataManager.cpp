#include "stdafx.h"
#include "iniDataManager.h"


iniDataManager::iniDataManager()
{
}


iniDataManager::~iniDataManager()
{
}

HRESULT iniDataManager::init()
{
	return E_NOTIMPL;
}

void iniDataManager::release()
{
}

void iniDataManager::addData(const char * subject, const char * title, const char * body)
{
}

void iniDataManager::iniSave(const char * fileName)
{
}

char * iniDataManager::loadDataString(const char * fileName, const char * subject, const char * title)
{
	return nullptr;
}

int iniDataManager::loadDataInteger(const char * fileName, const char * subject, const char * title)
{
	return 0;
}
