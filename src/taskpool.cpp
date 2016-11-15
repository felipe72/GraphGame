#include <mutex>
#include <iostream>

#include "taskpool.hpp"

void threadInit(){
	std::cout << "Thread initialized\n";
}

void TaskPool::addMap(Map *t_map){
	m_map = t_map;
}

TaskPool::TaskPool(){
	checkTasks = std::thread(&TaskPool::taskLoop, this);
	for(int i=0; i<MAX_NUMBER_THREADS; i++){
		threadPool[i] = std::thread(threadInit);
	}
}

TaskPool::~TaskPool(){
	if(checkTasks.joinable()){
		checkTasks.join();
	}
	for(int i=0; i<MAX_NUMBER_THREADS; i++){
		threadPool[i].join();
	}
}

void TaskPool::add(typeFunction t_function, int priority=1){
	std::mutex mx;

	mx.lock();
	m_functions.push(Task(priority, t_function));
	mx.unlock();
}

void noFunction(){
	std::cout << "No functions left\n";
}

typeFunction TaskPool::remove(){
	std::mutex mx;
	Task task;

	// int priority;
	typeFunction function;

	if(not m_functions.empty()){
		mx.lock();
		task = m_functions.front();
		m_functions.pop();
		// add(task.function());
		mx.unlock();

		// priority = task.priority();
		function = task.function();
		removed_tasks.push(task);
	}
	else{
		// priority = -1;
		function = std::bind(noFunction);
	}

	return function;
}

void TaskPool::taskLoop(){
	while(active){
		// std::cout << "Oi\n";
		if(not m_functions.empty())
			invokeAll();
	}
}

void TaskPool::invokeAll(){
	for(int i=0; not m_functions.empty(); i = (i+1)%MAX_NUMBER_THREADS){
		typeFunction f = remove();
		if(threadPool[i].joinable()){
			threadPool[i].join();
			threadPool[i] = std::thread(f);
		}
	}
	bool flag = true;
	for(int i=0; i<MAX_NUMBER_THREADS; i = (i+1)%MAX_NUMBER_THREADS){
		if(i==0)
			flag = true;
		if(!threadPool[i].joinable())
			flag = false;
		else if(i == MAX_NUMBER_THREADS -1 and flag == true){
			m_map->print();
			break;
		}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	reAdd();
}

void TaskPool::reAdd(){
	while(not removed_tasks.empty()){
		auto task = removed_tasks.front();
		removed_tasks.pop();
		m_functions.push(task);
	}
}


void TaskPool::terminate(){
	std::mutex mx;
	mx.lock();

	while(not removed_tasks.empty()){
		removed_tasks.pop();
	}
	while(not m_functions.empty()){
		m_functions.pop();
	}
	active = false;
	mx.unlock();	
}