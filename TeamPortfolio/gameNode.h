#pragma once
#include "image.h" //�߰�

//����۶�� �� ��Ʈ�� �̹����� �ϳ� �����صд�

#define FRAMETICK 6

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZEX, WINSIZEY);//�߰�
static POINT _camera = { 0, 0 };

//�������� �ٲ۴�, ��ü���� ���α׷����� ���ϰ� ���� �ϱ����� ������ �ٲ���
//�������뿡�� ����۸� ȣ���ϱ⺸��, �� �ϳ��� ��DC�� �����ΰ� �ű�� ������ �������ϴ°��� ���ϴ�

class gameNode
{
private:
	//��ü ����� �߰�
	HDC _hdc;
	bool _managerInit;		         //�Ŵ������� �ʱ�ȭ �� ���̳�
public:
	//��ü ����� �߰�
	virtual HRESULT init(void);		//�ʱ�ȭ �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release(void);		//�޸� ���� ����
	virtual void update(void);		//������Ʈ(����)
	virtual void render(void);	    //�׷��ִ� �Լ�

	virtual POINT getCamera() { return _camera; }
	virtual void setCamera(POINT position) {
		_camera = position;
	}
	virtual POINT getCameraCenter() {
		return { _camera.x + WINSIZEX / 2, _camera.y + WINSIZEY / 2 };
	}
	virtual void setCameraCenter(POINT position) { setCamera({position.x - WINSIZEX / 2, position.y - WINSIZEY / 2 }); }
	image* getBackBuffer(void) { return _backBuffer; }
	HDC getMemDC() { return _backBuffer->getMemDC(); }//�߰�
	HDC getHDC() { return _hdc; }//�߰�


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

