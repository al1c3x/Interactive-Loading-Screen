#pragma once
#include "AGameObject.h"
#include "TextureManager.h"
#include <SFML/Audio.hpp>

class BGObject : public AGameObject
{
	public: 
		BGObject(String name);
		void initialize();
		void processInput(sf::Event event);
		void update(sf::Time deltaTime);
	private:
		const float SPEED_MULTIPLIER = 1000.0f;
		TextureManager::TextureList textureList;
		int Index = 0;
		float TimeLimit = 10.0f;
		float TimeElapse = 0.0f;
		sf::Music music;

};

