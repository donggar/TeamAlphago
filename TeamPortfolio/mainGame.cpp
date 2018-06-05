#include "stdafx.h"
#include "mainGame.h"


mainGame::mainGame()
{
}


mainGame::~mainGame()
{
}

HRESULT mainGame::init(void)
{
	gameNode::init(true);  
	IMAGEMANAGER->addImage("taxi", "car_taxi.bmp", 64, 36, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bug", "car_bug.bmp", 52, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("test", "temprun.bmp", 144, 20, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("wall", "wall_1.bmp", 128, 64, 2, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("a", WINSIZEX, WINSIZEY);
	vehicle* temp;
	temp = new vehicle;
	temp->init(IMAGEMANAGER->findImage("taxi"), 100.0f, 100.0f, 7.5f, 0.0f, 0.15f, 0.008f, 0);
	_vCars.push_back(temp);
	temp = new vehicle;
	temp->init(IMAGEMANAGER->findImage("bug"), 200.0f, 100.0f, 5.0f, 0.0f, 0.1f, 0.01f, 0);
	_vCars.push_back(temp);
	_character = new npc;
	_character->init(IMAGEMANAGER->findImage("test"), 300.0f, 100.0f, 1.0f, 0.0f);
	_player = _character;
	_vWalls.push_back(new wall);
	//_vWalls.back()->init(IMAGEMANAGER->findImage("wall"), );
	_zoom = 1.0f;
	return S_OK;
}

void mainGame::release(void)  
{
	gameNode::release();
}

void mainGame::update(void)	  
{
	gameNode::update();
	_player->control();
	for (vector<vehicle*>::iterator it = _vCars.begin(); it != _vCars.end(); it++) {
		if ((*it) == _player) continue;
		else (*it)->update();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE)) {
		if (_player != _character) {
			_character->setPosition(_player->getDoor());
			_character->setAngle(_player->getAngle() - PI / 2);
			_player = _character;
		}
		else {
			for (vector<vehicle*>::iterator it = _vCars.begin(); it != _vCars.end(); it++) {
				if (getDistancePointf(_character->getPosition(), (*it)->getDoor()) < 15.0f) {
					_player = *it;
					break;
				}
			}
		}
	}
	//if (KEYMANAGER->isStayKeyDown('A')) _zoom -= 0.05f;
	//if (KEYMANAGER->isStayKeyDown('D')) _zoom += 0.05f;
	//_zoom = clip(_zoom, 1.0f, 2.0f);
	_zoom = 1.8f - _player->getVelocity() / _player->getSpeed();
	_zoom = clip(_zoom, 1.0f, 1.8f);
	setCameraCenter({ long(_player->getPosition().x), long(_player->getPosition().y) });
}

void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	if (_player == _character) _character->render();
	for (vector<vehicle*>::iterator it = _vCars.begin(); it != _vCars.end(); it++) {
		(*it)->render();
	}
	RECT bound = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX / _zoom, WINSIZEY / _zoom);
	StretchBlt(IMAGEMANAGER->findImage("a")->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, this->getBackBuffer()->getMemDC(), bound.left, bound.top, bound.right - bound.left, bound.bottom - bound.top, SRCCOPY);
	TIMEMANAGER->render(IMAGEMANAGER->findImage("a")->getMemDC());
	IMAGEMANAGER->findImage("a")->render(getHDC());
}