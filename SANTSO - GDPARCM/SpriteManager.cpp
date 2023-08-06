#include "SpriteManager.h"
#include "TextureManager.h"
#include "BaseRunner.h"
#include <iostream>

SpriteManager::SpriteManager(String name):AGameObject(name)
{
}

void SpriteManager::initialize()
{
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();

	for(int i=1; i <= 7;i++)
	{
		string name = "Emote" + std::to_string(i);

		std::cout << name << endl;
		sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(name, 0);
		textureList.push_back(texture);
	}
	this->sprite->setPosition(25, BaseRunner::WINDOW_HEIGHT - 450);
	this->sprite->setTexture(*textureList[Index]);

}

void SpriteManager::processInput(sf::Event event)
{
}

void SpriteManager::update(sf::Time deltaTime)
{


	TimeElapse += deltaTime.asSeconds();
	if(TimeElapse> 1.0f)
	{
		Index++;
		TimeElapse = 0;
	}

	if(Index == 7)
	{
		Index = 0;
	}

	this->sprite->setTexture(*textureList[Index]);

	
}
