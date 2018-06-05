#pragma once
#include "animation.h"

class image
{
	//�̹��� �ҷ����� Ÿ��
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		//���ҽ��κ���
		LOAD_FILE,			//���Ϸκ���
		LOAD_EMPTY,			//�� ��Ʈ�����κ���
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD	resID;	    //���ҽ� �ҷ��ö� ���Ǵ� �������� �ѹ�
		HDC		hMemDC;		//�޸� DC
		HBITMAP hBit;	    //��Ʈ��
		HBITMAP hOBit;	    //�õ� ��Ʈ��
		float	x;			//�̹��� X��ǥ (left)
		float	y;			//�̹��� Y��ǥ (top) 
		int		width;		//���� ũ��(�̹���)
		int		height;		//���� ũ��(�̹���)

		int		currentFrameX;	//���� ������ X  
		int		currentFrameY;	//���� ������ Y  
		int		maxFrameX;		//�ִ� ������ X  
		int		maxFrameY;		//�ִ� ������ Y  
		int		frameWidth;		//������ ����ũ��
		int		frameHeight;	//������ ����ũ��
		BYTE	loadType;	//�̹��� �ҷ��� Ÿ��
		RECT	boundingBox;	//�ٿ�� �ڽ�(�浹üũ�� �ڽ�) 

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			width = 0;
			height = 0;
			x = 0;
			y = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			boundingBox = RectMake(0, 0, 0, 0);
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;
private:
	LPIMAGE_INFO	_imageInfo;		//�̹��� ���� ����ü
	CHAR*			_fileName;		//���� �̸�
	BOOL			_trans;			//Ʈ�����÷� ����(Ư�� �ȼ��� ����)
	COLORREF		_transColor;	//�����Ѵٸ� � �÷�?

	BLENDFUNCTION   _blendFunc;     //���ĺ��忡 ���� �Լ�
	LPIMAGE_INFO    _blendImage;	//���ĺ��� ���� �̹���
public:
	image();
	~image();

	//�� ��Ʈ�� �̹��� �ʱ�ȭ
	HRESULT init(int width, int height);
	//���Ϸκ��� �̹��� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);
	//���Ϸκ��� �̹��� �ʱ�ȭ           ó�� ���� ��ǥ      ����       ����
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE);

	//�̹��� + �������ʱ�ȭ
	HRESULT init(const char* fileName, float x, float y, int width, int height,
		int frameX, int frameY, BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));

	HRESULT init(const char* fileName, int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = RGB(255, 0, 255));

	//�̹��� ������
	void release(void);

	//Ȥ�� Ʈ����ó���� �ٸ� �ȼ������� �ٲ���Ѵٸ�
	void setTransColor(BOOL trans, COLORREF transColor);

	void render(HDC hdc);

	//�������Լ� �Ѹ�DC , �Ѹ���X(Left), �Ѹ���Y(top)
	void render(HDC hdc, int destX, int destY);

	//�������Լ� �Ѹ�DC , �Ѹ���X(Left), �Ѹ���Y(top)
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//��������      �׸� DC, �׷��ִ� ����(�׸����)        �����¿���X, Y
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	//�����ӷ���
	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	
	void alphaRender(HDC hdc, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, BYTE alpha);
	
	void plgRender(HDC hdc, POINT* plg);
	void plgRender(HDC hdc, int srcX, int srcY, int srcWidth, int srcHeight, POINT* plg);

	void rotateRender(HDC hdc, int destX, int destY, float angle);
	void rotateRender(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, float angle);

	void aniRender(HDC hdc, int destX, int destY, animation* ani);

	inline HDC getMemDC() { return _imageInfo->hMemDC; }


	//==============================================
	// ## �̹��� ��� ���Ǹ� ���� ������, ������
	//==============================================


	//�̹��� �ѷ��ִ� ��ġ X
	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX(void) { return _imageInfo->x; }

	//�̹��� �ѷ��ִ� ��ġ Y
	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY(void) { return _imageInfo->y; }

	//�̹����� ������ǥ�� �̵�
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX(void)
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) : _imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY(void)
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) : _imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }

	//�ٿ�� �ڽ�
	inline RECT boundingBox(void)
	{
		RECT rc = {
			int(_imageInfo->x),
			int(_imageInfo->y),
			int(_imageInfo->frameWidth),
			int(_imageInfo->frameHeight) };

		return rc;
	}

	//������
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }

	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }
};

