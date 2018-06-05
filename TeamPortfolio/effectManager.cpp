#include "stdafx.h"
#include "effectManager.h"
#include "effect.h"


effectManager::effectManager()
{
}


effectManager::~effectManager()
{
}

HRESULT effectManager::init()
{
	return S_OK;
}

void effectManager::release()
{
	iterTotalEffect vIter;
	iterEffect		mIter;
	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter) {
		mIter = vIter->begin();
		for (; mIter != vIter->end(); ) {
			if (mIter->second.size() != 0) {
				iterEffects vArrIter = mIter->second.begin();
				for (; vArrIter != mIter->second.end(); ) {
					(*vArrIter)->release();
					delete *vArrIter;
					vArrIter = mIter->second.erase(vArrIter);
				}
			}
			else ++mIter;
		}
	}
}

void effectManager::update()
{
	iterTotalEffect vIter;
	iterEffect		mIter;
	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter) {
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter) {
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter) {
				(*vArrIter)->update();
			}
		}
	}
}

void effectManager::render()
{
	iterTotalEffect vIter;
	iterEffect		mIter;
	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter) {
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter) {
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter) {
				(*vArrIter)->render();
			}
		}
	}
}

void effectManager::addEffect(string effectName, const char * imageName, int imageW, int imageH, int effectW, int effectH, int fps, int elapsedTime, int buffer)
{
	image* img;
	arrEffects vEffectBuffer;
	arrEffect mArrEffect;
	if (IMAGEMANAGER->findImage(imageName)) {
		img = IMAGEMANAGER->findImage(imageName);
	}
	else {
		img = IMAGEMANAGER->addImage(imageName, imageName, imageW, imageH, true, RGB(255, 0, 255));
	}
	for (int i = 0; i < buffer; ++i) {
		vEffectBuffer.push_back(new effect);
		vEffectBuffer[i]->init(img, effectW, effectH, fps, elapsedTime);
	}
	mArrEffect.insert(pair<string, arrEffects>(effectName, vEffectBuffer));
	_vTotalEffect.push_back(mArrEffect);
}

void effectManager::play(string effectName, int x, int y)
{
	iterTotalEffect vIter;
	iterEffect		mIter;
	for (vIter = _vTotalEffect.begin(); vIter != _vTotalEffect.end(); ++vIter) {
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter) {
			if (!(mIter->first == effectName)) break;
			iterEffects vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter) {
				if ((*vArrIter)->getIsRunning()) continue;
				(*vArrIter)->startEffect(x, y);
				return;
			}
		}
	}
}
