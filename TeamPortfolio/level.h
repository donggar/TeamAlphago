#pragma once
#include "gameNode.h"

struct tile
{
	image* _texture;
	bool _solid;
};

struct wall : public tile
{

};

class level
{
private:
	typedef map<unsigned char, tile>			mapTileList;
	typedef map<unsigned char, tile>::iterator	mapTileIter;
private:
	int _width;
	int _height;
	unsigned char* _tiles;
	mapTileList _tilePreset;
public:
	level();
	~level();

	HRESULT init(void);
	void release(void);
	void render(void);
	
	bool getTest(int x, int y) {
		if (x * y > _width * _height || x < 0 || y < 0) return false;
		return _tilePreset.find(_tiles[_width * y + x])->second._solid;
	}
};