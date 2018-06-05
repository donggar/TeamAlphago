#pragma once
#include "gameNode.h"

class tile : public gameNode
{
private:
	image * _texture;
	bool _solid;
public:
	tile();
	~tile();

	HRESULT init();
	void render(void);

	bool isSolid(void) { return _solid; }
};