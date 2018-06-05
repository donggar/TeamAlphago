#include "stdafx.h"
#include "tile.h"


tile::tile() :
	_texture(NULL),
	_solid(false)
{
}


tile::~tile()
{
}

HRESULT tile::init()
{
	return S_OK;
}

void tile::render(void)
{
}