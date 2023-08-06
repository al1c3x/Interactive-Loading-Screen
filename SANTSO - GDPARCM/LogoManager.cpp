#include "LogoManager.h"
#include "TextureManager.h"
#include "BaseRunner.h"

LogoManager::LogoManager(sf::String name):AGameObject(name)
{
}

void LogoManager::initialize()
{
	this->sprite = new sf::Sprite();
	this->sprite->setTexture(*TextureManager::getInstance()->getFromTextureMap("genshinlogo",0));
	this->sprite->setScale(0.1, 0.1);
	this->sprite->setOrigin(0, 0);
	this->sprite->setPosition(25 , BaseRunner::WINDOW_HEIGHT - 150);
}

void LogoManager::processInput(sf::Event event)
{
}

void LogoManager::update(sf::Time deltaTime)
{
}
