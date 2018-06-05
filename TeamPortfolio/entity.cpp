#include "stdafx.h"
#include "entity.h"


entity::entity()
{
}


entity::~entity()
{
}

HRESULT entity::init(image * image, float x, float y, float speed, float angle)
{
	_image = image;
	_position.x = x;
	_position.y = y;
	_speed = speed;
	_angle = angle;
	_radius = 10.0f;
	_countX = _countY = 0;
	return S_OK;
}

void entity::release(void)
{
}

void entity::update(void)
{
}

void entity::render(void)
{
	_image->rotateRender(getMemDC(), _position.x - getCamera().x, _position.y - getCamera().y, (_countX / FRAMETICK) * _image->getFrameWidth(), (_countY / FRAMETICK) * _image->getFrameHeight(), _image->getFrameWidth(), _image->getFrameHeight(), _angle);
}