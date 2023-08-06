#include "BGObject.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"

BGObject::BGObject(string name) : AGameObject(name)
{
}

void BGObject::initialize()
{
	if (!this->music.openFromFile("Media/genshin.ogg"))
		std::cout << "Audio file not found!";
	this->music.setLoop(true);
	this->music.setVolume(50);
	this->music.play();
	std::cout << "Declared as " << this->getName() << "\n";

	//assign texture
	this->sprite = new sf::Sprite();

	for (int i = 1; i <= 9; i++)
	{
		string name = "BG" + std::to_string(i);

		std::cout << name << endl;
		sf::Texture* texture = TextureManager::getInstance()->getFromTextureMap(name, 0);
		textureList.push_back(texture);
	}
	this->sprite->setTexture(*textureList[Index]);

}

void BGObject::processInput(sf::Event event)
{
}





void BGObject::update(sf::Time deltaTime)
{

	TimeElapse += deltaTime.asSeconds();
	if (TimeElapse > 10 )
	{
		Index++;
		TimeElapse = 0;
	}
	if(Index == 8)
	{
		Index = 0;
	}

	this->sprite->setTexture(*textureList[Index]);
}
