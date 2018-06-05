#pragma once
#include "entity.h"

class NPC;

class vehicle : public entity
{
protected:
	POINT _door;
	float _acceleration;
	float _handling;
	float _velocity;
	vector<NPC*> _passenger;
public:
	vehicle();
	~vehicle();

	HRESULT init(image* image, float x, float y, float speed, float angle, float acceleration, float handling, int door);
	virtual void update();
	virtual void control();
	virtual void move();

	POINTF getDoor(void) {
		POINTF vector = { cosf(_angle), sinf(_angle) };
		return {
			_position.x + _door.x * vector.x - _door.y * vector.y,
			_position.y + _door.x * vector.y + _door.y * vector.x
		};
	}
	float getVelocity(void) { return abs(_velocity); }
};

