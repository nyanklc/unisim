#include "vuniverse_engine.h"

vuniverse::VuniverseEngine::VuniverseEngine()
{
	_isRunning = false;
}

void vuniverse::VuniverseEngine::start()
{
	_isRunning = true;
}

bool vuniverse::VuniverseEngine::isRunning()
{
	return _isRunning;
}

void vuniverse::VuniverseEngine::stop()
{
	_isRunning = false;
}
