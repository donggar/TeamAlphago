#include "stdafx.h"
#include "NPC.h"

npc::npc()
{
}

npc::~npc()
{
}

void npc::update()
{
	move();
}

void npc::control()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _angle -= 0.12f;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _angle += 0.12f;
	_angle = fmod(_angle, PI2);
	if (KEYMANAGER->isStayKeyDown(VK_UP)) {
		move();
		_countX++;
		if (_countX > _image->getMaxFrameX() * FRAMETICK) _countX = 0;
	}
	else _countX = 0;
}

void npc::move()
{
	POINT probe = { (_speed + _radius), 0 };
	probe = rotatePoint(probe, { cosf(_angle), sinf(_angle) });
	_position.x += cosf(_angle) * _speed;
	_position.y += sinf(_angle) * _speed;
}