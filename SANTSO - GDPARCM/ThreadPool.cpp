#include "ThreadPool.h"
#include "PoolWorkerThread.h"
#include "TextureManager.h"

ThreadPool::ThreadPool(String name, int numWorkers)
{
	this->name = name;
	this->numWorkers = numWorkers;

	for(int i=0; i<numWorkers; i++)
	{
		this->inactiveThreads.push(new PoolWorkerThread(i, this));
	}
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::startScheduler()
{
	this->running = true;
	this->start();
}

void ThreadPool::stopScheduler()
{
	this->running = false;
}

void ThreadPool::scheduleTask(IWorkerAction* action)
{
	this->pendingActions.push(action);
}

void ThreadPool::loadBatchAssets(int startingIndex, int batchSize, IExecutionEvent* execEvent)
{
	for(int i=0; i<batchSize; i++)
	{
		TextureManager::getInstance()->loadBatchStreamAsset(startingIndex + 1, execEvent, this);
	}
}

void ThreadPool::run()
{
	while(this->running)
	{
		if(this->pendingActions.empty()==false)
		{
			if(this->inactiveThreads.empty() == false)
			{
				PoolWorkerThread* workerThread = this->inactiveThreads.front();
				this->inactiveThreads.pop();
				this->activeThreads[workerThread->getThreadID()] = workerThread;

				workerThread->assignTask(this->pendingActions.front());
				pendingActions.pop();
				workerThread->start();

			}
			else
			{
				//std::cout << "[ThreadPool " << this->name << "] No more available worker thread" << std::endl;
			}
		}
		else
		{
			//std::cout << "[ThreadPool " << this->name << "] No actions scheduled" << std::endl;
		}
	}
}

void ThreadPool::onFinished(int threadID)
{
	if(this->activeThreads[threadID] !=nullptr)
	{
		delete this->activeThreads[threadID];
		this->activeThreads.erase(threadID);

		this->inactiveThreads.push(new PoolWorkerThread(threadID, this));
	}
}
