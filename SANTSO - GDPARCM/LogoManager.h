#pragma once
#include <string>
#include "TextureManager.h"
#include "AGameObject.h"

class LogoManager:public AGameObject
{
public:
	LogoManager(sf::String name);
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	
private:

};

