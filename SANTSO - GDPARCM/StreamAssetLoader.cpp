#include "StreamAssetLoader.h"
#include "StringUtils.h"
#include "TextureManager.h"
#include <vector>


StreamAssetLoader::StreamAssetLoader(String path, IExecutionEvent* execEvent)
{
	this->path = path;
	this->execEvent = execEvent;
}

StreamAssetLoader::~StreamAssetLoader()
{
	std::cout << "Destroying stream asset loader" << std::endl;
}

void StreamAssetLoader::run()
{
	
}

void StreamAssetLoader::onStartTask()
{
	std::vector<String> tokens = StringUtils::split(path, '/');
	String assetName = StringUtils::split(tokens[tokens.size() - 1], '.')[0];

	IETThread::sleep(1000);
	TextureManager::getInstance()->instantiateAsTexture(path, assetName, true);
	std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
	this->execEvent->onFinishedExecution();

	delete this;
}
