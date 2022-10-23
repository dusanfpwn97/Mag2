#include "InputManager.h"

efe::InputManager::InputManager() :
	_mouseCoords(0.f)
{
}

efe::InputManager::~InputManager()
{
}

void efe::InputManager::pressKey(unsigned int keyID)
{
	_keyMap[keyID] = true;
}

void efe::InputManager::releaseKey(unsigned int keyID)
{
	_keyMap[keyID] = false;
}

void efe::InputManager::setMouseCoords(float x, float y)
{
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}

bool efe::InputManager::isKeyPressed(unsigned int keyID)
{
	auto it = _keyMap.find(keyID);

	if (it != _keyMap.end())
	{
		return it->second;
	}
	return false;
}



