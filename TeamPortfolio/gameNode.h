#pragma once
#include "image.h" //추가

//백버퍼라는 빈 비트맵 이미지를 하나 설정해둔다

#define FRAMETICK 6

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);//추가
static POINT _camera = { 0, 0 };

//구조부터 바꾼다, 객체지향 프로그래밍을 편하고 쉽게 하기위해 구조를 바꾸자
//여러군대에서 백버퍼를 호출하기보단, 단 하나의 백DC를 만들어두고 거기로 접근을 용이케하는것이 편하다

class gameNode
{
private:
	//전체 지우고 추가
	HDC _hdc;
	bool _managerInit;		         //매니저등을 초기화 할 것이냐
public:
	//전체 지우고 추가
	virtual HRESULT init(void);		//초기화 함수
	virtual HRESULT init(bool managerInit);
	virtual void release(void);		//메모리 관련 해제
	virtual void update(void);		//업데이트(연산)
	virtual void render(void);	    //그려주는 함수

	virtual POINT getCamera() { return _camera; }
	virtual void setCamera(POINT position) {
		_camera = position;
	}
	virtual POINT getCameraCenter() {
		return { _camera.x + WINSIZEX / 2, _camera.y + WINSIZEY / 2 };
	}
	virtual void setCameraCenter(POINT position) { setCamera({position.x - WINSIZEX / 2, position.y - WINSIZEY / 2 }); }
	image* getBackBuffer(void) { return _backBuffer; }
	HDC getMemDC() { return _backBuffer->getMemDC(); }//추가
	HDC getHDC() { return _hdc; }//추가


	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);

	gameNode();
	virtual ~gameNode();
};

typedef struct tagPointFloat
{
	float x, y;
} POINTF;

inline float getDistancePointf(POINTF a, POINTF b) {
	float x = a.x - b.x;
	float y = a.y - b.y;
	return sqrt(x * x + y * y);
}

inline POINTF normalizeVector(POINTF vector) {
	float distance = sqrt(vector.x * vector.x + vector.y * vector.y);
	return { vector.x / distance, vector.y / distance };
}

inline POINTF scaleVector(POINTF vector, float scalar) {
	return { vector.x * scalar, vector.y * scalar };
}

inline POINT rotatePoint(POINT point, POINTF vector) {
	return {
		static_cast<long>(point.x * vector.x - point.y * vector.y),
		static_cast<long>(point.x * vector.y + point.y * vector.x)
	};
}

inline POINT scalePoint(POINT point, int scalar) {
	return { point.x * scalar, point.y * scalar };
}

inline POINT flipPointHorizontal(POINT point) {
	return { -point.x, point.y };
}

inline void makeParallelogram(POINT* plg, POINT axis, POINT dimension) {
	plg[0] = { -axis.x, -axis.y };
	plg[1] = { dimension.x - axis.x, -axis.y };
	plg[2] = { -axis.x, dimension.y - axis.y };
	plg[3] = { dimension.x - axis.x, dimension.y - axis.y };
}

inline void copyParallelogram(POINT* newPlg, POINT* srcPlg) {
	for (int i = 0; i < 4; i++)
		newPlg[i] = srcPlg[i];
}
inline void rotateParallelogram(POINT* plg, POINTF vector) {
	for (int i = 0; i < 4; i++)
		plg[i] = rotatePoint(plg[i], vector);
}

inline void translateParallelogram(POINT* plg, POINTF position) {
	for (int i = 0; i < 4; i++) {
		plg[i].x += static_cast<long>(position.x);
		plg[i].y += static_cast<long>(position.y);
	}
}

inline void flipParallelogramHorizontal(POINT* plg) {
	for (int i = 0; i < 4; i++)
		plg[i] = flipPointHorizontal(plg[i]);
}

inline void transformParallelogram(POINT* plg, POINTF rotation, POINTF translation) {
	rotateParallelogram(plg, rotation);
	translateParallelogram(plg, translation);
}

