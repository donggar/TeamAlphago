#pragma once
#include "gameNode.h"

class entity : public gameNode
{
protected:
	POINTF _position;
	float _speed;
	float _angle;
	float _radius;
	image* _image;
	int _countX;
	int _countY;
public:
	entity();
	~entity();

	virtual HRESULT init(image* image, float x, float y, float speed, float angle);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void control() {};
	virtual void move() {};

	POINTF getPosition(void) { return _position; }
	void setPosition(POINTF position) { _position = position; }
	float getRadius(void) { return _radius; }
	float getSpeed(void) { return _speed; }
	float getAngle(void) { return _angle; }
	void setAngle(float angle) { _angle = angle; }
	virtual float getVelocity(void) { return 0; }
	image* getImage(void) { return _image; }
	virtual POINTF getDoor(void) { return { 0, 0 }; }
};

