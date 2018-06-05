#include "stdafx.h"
#include "vehicle.h"

#define FRICTION 0.02f

vehicle::vehicle()
{
}

vehicle::~vehicle()
{
}

HRESULT vehicle::init(image * image, float x, float y, float speed, float angle, float acceleration, float handling, int door)
{
	entity::init(image, x, y, speed, angle);
	_acceleration = acceleration;
	_handling = handling;
	_velocity = 0.0f;
	_radius = getDistance(0, 0, _image->getFrameWidth() / 2, _image->getFrameHeight() / 2);
	_door = { door, -(_image->getFrameHeight() / 2 + 5) };
	return S_OK;
}

void vehicle::update()
{
	move();
}

void vehicle::control()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _angle -= _handling * _velocity;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _angle += _handling * _velocity;
	_angle = fmod(_angle, PI2);
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		_velocity += _acceleration;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) {
		_velocity -= _velocity > 0 ? FRICTION * 2.0f : _acceleration / 1.6f;
	}
	move();
}

void vehicle::move()
{
	_position.x += cosf(_angle) * _velocity;
	_position.y += sinf(_angle) * _velocity;
	_velocity = _velocity < 0 ? min(_velocity + FRICTION, 0.0f) : max(_velocity - FRICTION, 0.0f);
	_velocity = clip(_velocity, -_speed, _speed);
}