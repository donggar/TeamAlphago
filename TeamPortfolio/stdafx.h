#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <algorithm>

#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "KeyManager.h"
#include "imageManager.h"
#include "txtData.h"
#include "soundManager.h"
#include "timeManager.h"
#include "effectManager.h"

using namespace std;

#define WINNAME (LPTSTR)TEXT("Neptune API")
#define WINSTARTX 50
#define WINSTARTY 50
#define WINSIZEX 900
#define WINSIZEY 600
#define WINSTYLE WS_CAPTION | WS_SYSMENU

#define RND randomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()

//안전한 메모리 관리
#define SAFE_DELETE(p) { if(p) {delete(p); (p) = NULL; }}
#define SAFE_RELEASE(p) {if(p) {(p)->release(); (p)=NULL; }}
#define SAFE_DELETE_ARRAY(p) { if(p) {delete[](p); (p) = NULL; }}

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
extern HINSTANCE	_hInstance;		//인스턴스 핸들
extern HWND			_hWnd;			//핸들
extern POINT        _ptMouse;       //마우스