#pragma once
#include "gameNode.h"
#include "vehicle.h"
#include "NPC.h"

class wall : public gameNode
{
private:
	POINT _begin;
	POINT _end;
	int _width;
	bool _side;
	image* _texture;
public:
	virtual HRESULT init(image* texture, POINT begin, POINT end) {
		_texture = texture;
		_begin = begin;
		_end = end;
		return S_OK;
	}
	virtual void release(void) {};
	virtual void update(void) {};
	virtual void render(void) {
		POINT center = getCamera();
	};
};

class mainGame : public gameNode
{
private:
	entity * _player;
	npc* _character;
	vector<vehicle*> _vCars;
	vector<wall*> _vWalls;
	float _zoom;
public:
	mainGame();
	~mainGame();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render();
};