#include "InputManager.h"

efe::InputManager::InputManager()
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

bool efe::InputManager::isKeyPressed(unsigned int keyID)
{
	auto it = _keyMap.find(keyID);

	if (it != _keyMap.end())
	{
		return it->second;
	}
	return false;
}



