#pragma once
#include "entity.h"

class npc : public entity
{
protected:
	POINT destination;
public:
	npc();
	~npc();

	virtual void update();
	virtual void control();
	virtual void move();
};
