#pragma once
#include "IETThread.h"
#include "IExecutionEvent.h"
#include "IWorkerAction.h"

class StreamAssetLoader:public IETThread, public IWorkerAction
{
private:
	typedef std::string String;
public:
	StreamAssetLoader(String path, IExecutionEvent* execEvent);

	~StreamAssetLoader();

private:
	void run() override;
	void onStartTask() override;
	String path;
	IExecutionEvent* execEvent;
};

