#ifndef TASK_POOL_HPP
#define TASK_POOL_HPP

#include <queue>
#include <thread>

#include "game.hpp"
#include "functiontype.hpp"
#include "task.hpp"
#include "map.hpp"

#define MAX_NUMBER_THREADS 4

class TaskPool{
public:
	TaskPool();
	~TaskPool();
	void add(typeFunction, int);
	void terminate();
	void addMap(Map*);

private:
	Map *m_map;
	bool active = true;
	typeFunction remove();
	void invokeAll();
	void taskLoop();
	void reAdd();
	std::queue<Task> m_functions;
	std::queue<Task> removed_tasks;
	std::thread checkTasks;
	std::thread threadPool[MAX_NUMBER_THREADS];
};

#endif