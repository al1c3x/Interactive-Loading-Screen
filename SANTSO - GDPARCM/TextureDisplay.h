#pragma once
#include "AGameObject.h"
#include "IExecutionEvent.h"
#include "ThreadPool.h"
#include "IWorkerAction.h"

class IconObject;
/// <summary>
/// Class that deals with displaying of streamed textures
/// </summary>
class TextureDisplay: public AGameObject, public IExecutionEvent,public IWorkerAction
{
public:
	TextureDisplay();
	void initialize();
	void processInput(sf::Event event);
	void update(sf::Time deltaTime);
	void onFinishedExecution();
	void onStartTask() override;

private:
	typedef std::vector<IconObject*> IconList;
	IconList iconList;

	enum StreamingType { BATCH_LOAD = 0, SINGLE_STREAM = 1 };
	const float STREAMING_LOAD_DELAY = 500.0f;
	const StreamingType streamingType = BATCH_LOAD;
	float ticks = 0.0f;
	bool startedStreaming = false;

	int columnGrid = 0; int rowGrid = 0;
	
	const int MAX_COLUMN = 28;
	const int MAX_ROW = 22;
	const int MAX_ICONS = 250;

	int numIconsLoaded = 0;
	int Index = 0;
	void spawnObject();

	ThreadPool* threadPool = nullptr;
	int batchSize = 1;
};

