#include "stdafx.h"
#include "image.h"

//ÄÄÆÄÀÏ·¯ Áö½Ã±â ³ª´Â ¸¶¼ÒÀÌ¹ÌÁö(32ºñÆ®) ¶óÀÌºê·¯¸®¸¦ »ç¿ëÇÏ°Ú´Ù
#pragma comment(lib, "msimg32.lib")

//¸â¹ö ÀÌ´Ï¼È¶óÀÌÁî
image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0))
{
}
image::~image()
{
}

//ºó ºñÆ®¸Ê ÀÌ¹ÌÁö ÃÊ±âÈ­
HRESULT image::init(int width, int height)
{
	//ÀÌ¹ÌÁö Á¤º¸°¡ ¹º°¡ÀÖ´Ù¸é ÇØÁ¦ÇØÁà¶ó
	if (_imageInfo != NULL) release();

	//DC¿µ¿ªÀ» »ç¿ëÇÏ°í½ÍÀ»¶§´Â °¡Á®¿Â´Ù
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//ºó DC¿µ¿ª »ý¼º
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height); //ºó ºñÆ®¸Ê ÀÌ¹ÌÁö »ý¼º
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;		//ÀÌ¹ÌÁö Å©±â °ª ´ëÀÔ ¹Þ´Â´Ù
	_imageInfo->height = height;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY); //ºó ºñÆ®¸Ê ÀÌ¹ÌÁö »ý¼º
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//ºñÆ®¸ÊÀÌ »ý¼ºÀÌ µÇÁö¾Ê¾Ò´Ù¸é
	if (_imageInfo->hBit == NULL)
	{
		//¸Þ¸ð¸® ÇØÁ¦ ½ÃÅ°°í
		release();
		return E_FAIL;	//½ÇÆÐÇß´Ù°í ¾Ë·Á¶ó
	}

	//°¡Á®¿Â DC¸¦ ÇØÁ¦
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//ÆÄÀÏ·ÎºÎÅÍ ÀÌ¹ÌÁö ÃÊ±âÈ­
HRESULT image::init(const char* fileName, int width, int height,
	BOOL trans, COLORREF transColor)
{
	//ÀÌ¹ÌÁö Á¤º¸°¡ ¹º°¡ÀÖ´Ù¸é ÇØÁ¦ÇØÁà¶ó
	if (_imageInfo != NULL) release();

	//DC¿µ¿ªÀ» »ç¿ëÇÏ°í½ÍÀ»¶§´Â °¡Á®¿Â´Ù
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//ºó DC¿µ¿ª »ý¼º
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;		//ÀÌ¹ÌÁö Å©±â °ª ´ëÀÔ ¹Þ´Â´Ù
	_imageInfo->height = height;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;

	//ÆÄÀÏ ±æÀÌ¸¦ ¾Ë¾Æ¿Â´Ù
	int len = strlen(fileName);


	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY); //ºó ºñÆ®¸Ê ÀÌ¹ÌÁö »ý¼º
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//ºñÆ®¸ÊÀÌ »ý¼ºÀÌ µÇÁö¾Ê¾Ò´Ù¸é
	if (_imageInfo->hBit == NULL)
	{
		//¸Þ¸ð¸® ÇØÁ¦ ½ÃÅ°°í
		release();
		return E_FAIL;	//½ÇÆÐÇß´Ù°í ¾Ë·Á¶ó
	}

	//°¡Á®¿Â DC¸¦ ÇØÁ¦
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor)
{
	//ÀÌ¹ÌÁö Á¤º¸°¡ ¹º°¡ÀÖ´Ù¸é ÇØÁ¦ÇØÁà¶ó
	if (_imageInfo != NULL) release();

	//DC¿µ¿ªÀ» »ç¿ëÇÏ°í½ÍÀ»¶§´Â °¡Á®¿Â´Ù
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//ºó DC¿µ¿ª »ý¼º
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;		//ÀÌ¹ÌÁö Å©±â °ª ´ëÀÔ ¹Þ´Â´Ù
	_imageInfo->height = height;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;


	//ÆÄÀÏ ±æÀÌ¸¦ ¾Ë¾Æ¿Â´Ù
	int len = strlen(fileName);


	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY); //ºó ºñÆ®¸Ê ÀÌ¹ÌÁö »ý¼º
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//ºñÆ®¸ÊÀÌ »ý¼ºÀÌ µÇÁö¾Ê¾Ò´Ù¸é
	if (_imageInfo->hBit == NULL)
	{
		//¸Þ¸ð¸® ÇØÁ¦ ½ÃÅ°°í
		release();
		return E_FAIL;	//½ÇÆÐÇß´Ù°í ¾Ë·Á¶ó
	}

	//°¡Á®¿Â DC¸¦ ÇØÁ¦
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//ÀÌ¹ÌÁö Á¤º¸°¡ ¹º°¡ÀÖ´Ù¸é ÇØÁ¦ÇØÁà¶ó
	if (_imageInfo != NULL) release();

	//DC¿µ¿ªÀ» »ç¿ëÇÏ°í½ÍÀ»¶§´Â °¡Á®¿Â´Ù
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//ºó DC¿µ¿ª »ý¼º
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;		//ÀÌ¹ÌÁö Å©±â °ª ´ëÀÔ ¹Þ´Â´Ù
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	//ÆÄÀÏ ±æÀÌ¸¦ ¾Ë¾Æ¿Â´Ù
	int len = strlen(fileName);


	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY); //ºó ºñÆ®¸Ê ÀÌ¹ÌÁö »ý¼º
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//ºñÆ®¸ÊÀÌ »ý¼ºÀÌ µÇÁö¾Ê¾Ò´Ù¸é
	if (_imageInfo->hBit == NULL)
	{
		//¸Þ¸ð¸® ÇØÁ¦ ½ÃÅ°°í
		release();
		return E_FAIL;	//½ÇÆÐÇß´Ù°í ¾Ë·Á¶ó
	}

	//°¡Á®¿Â DC¸¦ ÇØÁ¦
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	//ÀÌ¹ÌÁö Á¤º¸°¡ ¹º°¡ÀÖ´Ù¸é ÇØÁ¦ÇØÁà¶ó
	if (_imageInfo != NULL) release();

	//DC¿µ¿ªÀ» »ç¿ëÇÏ°í½ÍÀ»¶§´Â °¡Á®¿Â´Ù
	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);		//ºó DC¿µ¿ª »ý¼º
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;		//ÀÌ¹ÌÁö Å©±â °ª ´ëÀÔ ¹Þ´Â´Ù
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	//ÆÄÀÏ ±æÀÌ¸¦ ¾Ë¾Æ¿Â´Ù
	int len = strlen(fileName);


	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY); //ºó ºñÆ®¸Ê ÀÌ¹ÌÁö »ý¼º
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//ºñÆ®¸ÊÀÌ »ý¼ºÀÌ µÇÁö¾Ê¾Ò´Ù¸é
	if (_imageInfo->hBit == NULL)
	{
		//¸Þ¸ð¸® ÇØÁ¦ ½ÃÅ°°í
		release();
		return E_FAIL;	//½ÇÆÐÇß´Ù°í ¾Ë·Á¶ó
	}

	//°¡Á®¿Â DC¸¦ ÇØÁ¦
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
//***********************************************Ãß°¡

//ÀÌ¹ÌÁö ¸±¸®Áî
void image::release(void)
{
	//ÀÌ¹ÌÁöÁ¤º¸°¡ ÀÖ´Ù¸é
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);
		SAFE_DELETE(_blendImage);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}
}


//È¤½Ã Æ®·£½ºÃ³¸®¸¦ ´Ù¸¥ ÇÈ¼¿°ªÀ¸·Î ¹Ù²ã¾ßÇÑ´Ù¸é
void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

void image::render(HDC hdc)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//º¹»çµÉ ¿µ¿ªÀÇ DC
			_imageInfo->x,		//º¹»çµÉ ÁÂÇ¥ X
			_imageInfo->y,		//º¹»çµÉ ÁÂÇ¥ Y
			_imageInfo->width,	//º¹»çµÉ Å©±â(°¡·Î)
			_imageInfo->height,	//º¹»çµÉ Å©±â(¼¼·Î)
			_imageInfo->hMemDC,	//º¹»çÇØ¿Ã DC
			0, 0,				//º¹»çÇØ¿Ã ÁÂÇ¥X,Y
			_imageInfo->width,	//º¹»çÇØ¿Ã Å©±â
			_imageInfo->height,	//º¹»çÇØ¿Ã Å©±â
			_transColor);		//º¹»çÇØ¿Ã¶§ ¾î¶² ÄÃ·¯¸¦ »©°í °¡Á®¿Ã²¨³Ä
	}
	else
	{
		//¹é¹öÆÛ¿¡ ÀÖ´Â °ÍÀ» DC¿µ¿ªÀ¸·Î °í¼Óº¹»çÇØÁÖ´Â ÇÔ¼ö
		BitBlt(hdc,
			_imageInfo->x,
			_imageInfo->y,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//º¹»çµÉ ¿µ¿ªÀÇ DC
			destX,				//º¹»çµÉ ÁÂÇ¥ X
			destY,				//º¹»çµÉ ÁÂÇ¥ Y
			_imageInfo->width,	//º¹»çµÉ Å©±â(°¡·Î)
			_imageInfo->height,	//º¹»çµÉ Å©±â(¼¼·Î)
			_imageInfo->hMemDC,	//º¹»çÇØ¿Ã DC
			0, 0,				//º¹»çÇØ¿Ã ÁÂÇ¥X,Y
			_imageInfo->width,	//º¹»çÇØ¿Ã Å©±â
			_imageInfo->height,	//º¹»çÇØ¿Ã Å©±â
			_transColor);		//º¹»çÇØ¿Ã¶§ ¾î¶² ÄÃ·¯¸¦ »©°í °¡Á®¿Ã²¨³Ä
	}
	else
	{
		//¹é¹öÆÛ¿¡ ÀÖ´Â °ÍÀ» DC¿µ¿ªÀ¸·Î °í¼Óº¹»çÇØÁÖ´Â ÇÔ¼ö
		BitBlt(hdc, destX, destY,
			_imageInfo->width,
			_imageInfo->height,
			_imageInfo->hMemDC,
			0, 0, SRCCOPY);
	}
}


//·»´õ¸µÇÔ¼ö »Ñ¸±DC , »Ñ¸±°÷X(Left), »Ñ¸±°÷Y(top)
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//º¹»çµÉ ¿µ¿ªDC
			destX,					//º¹»çµÉ ÁÂÇ¥ X
			destY,					//º¹»çµÉ ÁÂÇ¥ Y
			sourWidth,				//º¹»çµÉ °¡·ÎÅ©±â
			sourHeight,				//º¹»çµÉ ¼¼·ÎÅ©±â
			_imageInfo->hMemDC,
			sourX, sourY,			//º¹»çÇØ¿Ã ÁÂÇ¥
			sourWidth,				//º¹»çÇØ¿Ã °¡·ÎÅ©±â
			sourHeight,				//º¹»çÇØ¿Ã ¼¼·ÎÅ©±â
			_transColor);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			sourWidth,
			sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			SRCCOPY);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	//È­¸é ¹ÛÀ¸·Î ³ª°¡¸é º¸Á¤ÇØÁØ´Ù
	//  -200					600				     -200   % 600
	if (offSetX < 0)
	{
		offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	}
	if (offSetY < 0)
	{
		offSetY = _imageInfo->height + (offSetY % _imageInfo->height);
	}
	//¿ÀÇÁ¼Â ¿µ¿ªÀ» ¹Þ¾Æ¿Ã º¯¼ö
	int sourWidth;
	int sourHeight;
	//±×·ÁÁÖ´Â ¿µ¿ª
	RECT rcDest;
	RECT rcSour;

	//±×·ÁÁÖ´Â ¿µ¿ªÀ» Àâ¾ÆÁØ´Ù
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;      //³Êºñ
	int drawAreaH = drawArea->bottom - drawAreaY;     //³ôÀÌ

	//YÃà ºÎÅÍ
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		sourHeight = rcSour.bottom - rcSour.top;

		//±×·ÁÁÖ´Â ¿µ¿ªÀÇ ³ôÀÌº¸´Ù yÃàÀÌ Å©¸é
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//È­¸é¹ÛÀ¸·Î ³ª°£¿µ¿ª¸¸Å­ »Ñ·ÁÁÙ À§Ä¡¿¡ »êÁ¤ÇÑ´Ù
		//»Ñ·ÁÁÖ´Â ¿µ¿ª
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//xÃà
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,//»Ñ·ÁÁÙ À§Ä¡ X, Y
				rcSour.left, rcSour.top,		//»Ñ·Á¿Ã À§Ä¡
				rcSour.right - rcSour.left,		//°¡·ÎÅ©±â
				rcSour.bottom - rcSour.top);	//¼¼·ÎÅ©±â
		}
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,								//º¹»çµÉ ¿µ¿ªÀÇ DC
			destX,								//º¹»çµÉ ÁÂÇ¥ X
			destY,								//º¹»çµÉ ÁÂÇ¥ Y
			_imageInfo->frameWidth,				//º¹»çµÉ Å©±â(°¡·Î)
			_imageInfo->frameHeight,			//º¹»çµÉ Å©±â(¼¼·Î)
			_imageInfo->hMemDC,					//º¹»çÇØ¿Ã DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//º¹»çÇØ¿Ã ÁÂÇ¥X,Y
			_imageInfo->frameWidth,				//º¹»çÇØ¿Ã Å©±â
			_imageInfo->frameHeight,			//º¹»çÇØ¿Ã Å©±â
			_transColor);						//º¹»çÇØ¿Ã¶§ ¾î¶² ÄÃ·¯¸¦ »©°í °¡Á®¿Ã²¨³Ä
	}
	else
	{
		//¹é¹öÆÛ¿¡ ÀÖ´Â °ÍÀ» DC¿µ¿ªÀ¸·Î °í¼Óº¹»çÇØÁÖ´Â ÇÔ¼ö
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,								//º¹»çµÉ ¿µ¿ªÀÇ DC
			destX,								//º¹»çµÉ ÁÂÇ¥ X
			destY,								//º¹»çµÉ ÁÂÇ¥ Y
			_imageInfo->frameWidth,				//º¹»çµÉ Å©±â(°¡·Î)
			_imageInfo->frameHeight,			//º¹»çµÉ Å©±â(¼¼·Î)
			_imageInfo->hMemDC,					//º¹»çÇØ¿Ã DC
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,	//º¹»çÇØ¿Ã ÁÂÇ¥X,Y
			_imageInfo->frameWidth,				//º¹»çÇØ¿Ã Å©±â
			_imageInfo->frameHeight,			//º¹»çÇØ¿Ã Å©±â
			_transColor);						//º¹»çÇØ¿Ã¶§ ¾î¶² ÄÃ·¯¸¦ »©°í °¡Á®¿Ã²¨³Ä
	}
	else
	{
		//¹é¹öÆÛ¿¡ ÀÖ´Â °ÍÀ» DC¿µ¿ªÀ¸·Î °í¼Óº¹»çÇØÁÖ´Â ÇÔ¼ö
		BitBlt(hdc, destX, destY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,
			currentFrameX * _imageInfo->frameWidth,
			currentFrameY * _imageInfo->frameHeight,
			SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	if (_trans) {
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else {
		AlphaBlend(hdc, _imageInfo->x, _imageInfo->y, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	if (_trans) {
		BitBlt(_blendImage->hMemDC, destX, destY, _imageInfo->width, _imageInfo->height, hdc, _imageInfo->x, _imageInfo->y, SRCCOPY);
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else {
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->frameHeight, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, BYTE alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;
	if (_trans) {
		BitBlt(_blendImage->hMemDC, destX, destY, srcWidth, srcHeight, hdc, srcX, srcY, SRCCOPY);
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, srcWidth, srcHeight, _imageInfo->hMemDC, 0, 0, srcWidth, srcHeight, _transColor);
		AlphaBlend(hdc, destX, destY, srcWidth, srcHeight, _blendImage->hMemDC, srcX, srcY, srcWidth, srcHeight, _blendFunc);
	}
	else {
		AlphaBlend(hdc, destX, destY, srcWidth, srcHeight, _imageInfo->hMemDC, srcX, srcY, srcWidth, srcHeight, _blendFunc);
	}
}

void image::plgRender(HDC hdc, POINT * plg)
{
	if (_trans) {
		RECT bound = {
			min(plg[0].x, min(plg[1].x, min(plg[2].x, plg[3].x))),
			min(plg[0].y, min(plg[1].y, min(plg[2].y, plg[3].y))),
			max(plg[0].x, max(plg[1].x, max(plg[2].x, plg[3].x))),
			max(plg[0].y, max(plg[1].y, max(plg[2].y, plg[3].y))) };
		int width = bound.right - bound.left;
		int height = bound.bottom - bound.top;
		for (int i = 0; i < 3; i++) {
			plg[i].x -= bound.left;
			plg[i].y -= bound.top;
		}
		BitBlt(_blendImage->hMemDC, 0, 0, width, height, hdc, bound.left, bound.top, SRCCOPY);
		PlgBlt(_blendImage->hMemDC, plg, _imageInfo->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, NULL, NULL, NULL);
		GdiTransparentBlt(hdc, bound.left, bound.top, width, height, _blendImage->hMemDC, 0, 0, width, height, _transColor);
	}
	else {
		PlgBlt(hdc, plg, _imageInfo->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, NULL, NULL, NULL);
	}
}

void image::plgRender(HDC hdc, int srcX, int srcY, int srcWidth, int srcHeight, POINT* plg)
{
	if (_trans) {
		RECT bound = {
			min(plg[0].x, min(plg[1].x, min(plg[2].x, plg[3].x))),
			min(plg[0].y, min(plg[1].y, min(plg[2].y, plg[3].y))),
			max(plg[0].x, max(plg[1].x, max(plg[2].x, plg[3].x))),
			max(plg[0].y, max(plg[1].y, max(plg[2].y, plg[3].y))) };
		int width = bound.right - bound.left;
		int height = bound.bottom - bound.top;
		for (int i = 0; i < 3; i++) {
			plg[i].x -= bound.left;
			plg[i].y -= bound.top;
		}
		BitBlt(_blendImage->hMemDC, 0, 0, width, height, hdc, bound.left, bound.top, SRCCOPY);
		PlgBlt(_blendImage->hMemDC, plg, _imageInfo->hMemDC, srcX, srcY, srcWidth, srcHeight, NULL, NULL, NULL);
		GdiTransparentBlt(hdc, bound.left, bound.top, width, height, _blendImage->hMemDC, 0, 0, width, height, _transColor);
	}
	else {
		PlgBlt(hdc, plg, _imageInfo->hMemDC, srcX, srcY, srcWidth, srcHeight, NULL, NULL, NULL);
	}
}


void image::rotateRender(HDC hdc, int destX, int destY, float angle) //HDC, 뿌릴 위치 X, Y, 각도
{
	//비트맵 중심을 축을 삼아 사각형 꼭지점 4개를 만듬
	POINT plg[4] = {
		{ -_imageInfo->frameWidth / 2, -_imageInfo->frameHeight / 2 },
		{ _imageInfo->frameWidth / 2, -_imageInfo->frameHeight / 2 },
		{ -_imageInfo->frameWidth / 2, _imageInfo->frameHeight / 2 },
		{ _imageInfo->frameWidth / 2, _imageInfo->frameHeight / 2 },
	};

	//꼭지점들을 각도만큼 회전하고 뿌릴 위치까지 이동
	for (int i = 0; i < 4; i++) {
		POINT temp;
		temp.x = static_cast<long>(plg[i].x * cosf(angle) - plg[i].y * sinf(angle)) + destX;
		temp.y = static_cast<long>(plg[i].x * sinf(angle) + plg[i].y * cosf(angle)) + destY;
		plg[i] = temp;
	}

	if (_trans) {
		//회전했을시 비트맵 크기 사각형
		RECT bound = {
			min(plg[0].x, min(plg[1].x, min(plg[2].x, plg[3].x))),
			min(plg[0].y, min(plg[1].y, min(plg[2].y, plg[3].y))),
			max(plg[0].x, max(plg[1].x, max(plg[2].x, plg[3].x))),
			max(plg[0].y, max(plg[1].y, max(plg[2].y, plg[3].y))) };
		int width = bound.right - bound.left;
		int height = bound.bottom - bound.top;
		for (int i = 0; i < 3; i++) {
			plg[i].x -= bound.left;
			plg[i].y -= bound.top;
		}
		BitBlt(_blendImage->hMemDC, 0, 0, width, height, hdc, bound.left, bound.top, SRCCOPY);
		PlgBlt(_blendImage->hMemDC, plg, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, NULL, NULL);
		GdiTransparentBlt(hdc, bound.left, bound.top, width, height, _blendImage->hMemDC, 0, 0, width, height, _transColor);
	}
	else {
		PlgBlt(hdc, plg, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, NULL, NULL, NULL);
	}
}

void image::rotateRender(HDC hdc, int destX, int destY, int srcX, int srcY, int srcWidth, int srcHeight, float angle)
{
	//비트맵 중심을 축을 삼아 사각형 꼭지점 4개를 만듬
	POINT plg[4] = {
		{ -_imageInfo->frameWidth / 2, -_imageInfo->frameHeight / 2 },
		{ _imageInfo->frameWidth / 2, -_imageInfo->frameHeight / 2 },
		{ -_imageInfo->frameWidth / 2, _imageInfo->frameHeight / 2 },
		{ _imageInfo->frameWidth / 2, _imageInfo->frameHeight / 2 },
	};

	//꼭지점들을 각도만큼 회전하고 뿌릴 위치까지 이동
	for (int i = 0; i < 4; i++) {
		POINT temp;
		temp.x = static_cast<long>(plg[i].x * cosf(angle) - plg[i].y * sinf(angle)) + destX;
		temp.y = static_cast<long>(plg[i].x * sinf(angle) + plg[i].y * cosf(angle)) + destY;
		plg[i] = temp;
	}

	if (_trans) {
		//회전했을시 비트맵 크기 사각형
		RECT bound = {
			min(plg[0].x, min(plg[1].x, min(plg[2].x, plg[3].x))),
			min(plg[0].y, min(plg[1].y, min(plg[2].y, plg[3].y))),
			max(plg[0].x, max(plg[1].x, max(plg[2].x, plg[3].x))),
			max(plg[0].y, max(plg[1].y, max(plg[2].y, plg[3].y))) };
		int width = bound.right - bound.left;
		int height = bound.bottom - bound.top;
		for (int i = 0; i < 3; i++) {
			plg[i].x -= bound.left;
			plg[i].y -= bound.top;
		}
		BitBlt(_blendImage->hMemDC, 0, 0, width, height, hdc, bound.left, bound.top, SRCCOPY);
		PlgBlt(_blendImage->hMemDC, plg, _imageInfo->hMemDC, srcX, srcY, srcWidth, srcHeight, NULL, NULL, NULL);
		GdiTransparentBlt(hdc, bound.left, bound.top, width, height, _blendImage->hMemDC, 0, 0, width, height, _transColor);
	}
	else {
		PlgBlt(hdc, plg, _imageInfo->hMemDC, srcX, srcY, srcWidth, srcHeight, NULL, NULL, NULL);
	}
}

void image::aniRender(HDC hdc, int destX, int destY, animation * ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}

