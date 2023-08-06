#include "TextureDisplay.h"
#include <iostream>
#include "TextureManager.h"
#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "IconObject.h"
TextureDisplay::TextureDisplay(): AGameObject("TextureDisplay")
{
	this->threadPool = new ThreadPool("Threadpool", 16);
	this->threadPool->startScheduler();
}

void TextureDisplay::initialize()
{
	
}

void TextureDisplay::processInput(sf::Event event)
{
	
}

void TextureDisplay::update(sf::Time deltaTime)
{
	this->ticks += BaseRunner::TIME_PER_FRAME.asMilliseconds();

	
	if(this->ticks >= STREAMING_LOAD_DELAY && numIconsLoaded <TextureManager::getInstance()->streamingAssetCount)
	{
		if(streamingType == StreamingType::SINGLE_STREAM)
		{
			this->ticks = 0.0f;
			TextureManager::getInstance()->loadSingleStreamAsset(TextureManager::getInstance()->getNumLoadedStreamTextures(), this);
		}
		else
		{
			this->threadPool->scheduleTask(this);
			this->ticks = 0;
		}
	}

	if(this->numIconsLoaded == this->MAX_ICONS && this->iconList.size() < this->MAX_ICONS)
	{
		IETThread::sleep(50);
		this->spawnObject();
	}
	
}

void TextureDisplay::onFinishedExecution()
{
	numIconsLoaded++;
}

void TextureDisplay::onStartTask()
{
	TextureManager::getInstance()->loadBatchStreamAsset(this->Index, this, threadPool);
	Index++;
}

void TextureDisplay::spawnObject()
{
	String objectName = "Icon_" + to_string(this->iconList.size());
	IconObject* iconObj = new IconObject(objectName, this->iconList.size());
	this->iconList.push_back(iconObj);

	//set position
	int IMG_WIDTH = 68; int IMG_HEIGHT = 68;
	float x = this->columnGrid * IMG_WIDTH;
	float y = this->rowGrid * IMG_HEIGHT;



	this->columnGrid++;
	if(this->columnGrid == this->MAX_COLUMN)
	{
		this->columnGrid = 0;
		this->rowGrid++;
	}
	GameObjectManager::getInstance()->addObject(iconObj);
	if(this->iconList.size()==this->MAX_ICONS)
	{
		this->iconList.clear();
	}
	
}
