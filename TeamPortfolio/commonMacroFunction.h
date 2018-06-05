#include "stdafx.h"

#define PI 3.141592f
#define PI2 PI * 2
#define PI8 float(PI/8.0f)
#define PI16 float(PI/16.0f)
#define PI32 float(PI/32.0f)

inline POINT PointMake(int x, int y) {
	POINT pt = { x, y };

	return pt;
}

inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);

}

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

template <typename T>
float getDistance(T startX, T startY, T endX, T endY)
{
	float x = static_cast<float>(endX - startX);
	float y = static_cast<float>(endY - startY);
	return sqrtf(x * x + y * y);
}

template <typename T>
T clip(const T& n, const T& lower, const T& upper) {
	return max(lower, min(n, upper));
}

template <typename T>
T sign(const T& n) {
	return n < 0 ? -1 : 1;
}