#pragma once
#include "gameNode.h"
#include "vehicle.h"
#include "NPC.h"

class mainGame : public gameNode
{
private:
	entity * _player;
	npc* _character;
	vector<vehicle*> _vCars;
	float _zoom;
public:
	mainGame();
	~mainGame();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render();
};