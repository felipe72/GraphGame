#include <iostream>
#include <functional>
#include <mutex>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>

#include "game.hpp"
#include "taskpool.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include "map.hpp"

using namespace std;

// bool active = true;
TaskPool taskPool;

void Game::start(){
	Map map;
	taskPool.addMap(&map);

	Player p;
	vector<Enemy> enemies;
	enemies.push_back(Enemy(Point(4, 4), &p, &map));
	for(Enemy e : enemies){
		map.addObject(&e);
		taskPool.add(std::bind(&Enemy::doAI, &e), 1);
	}
	map.addObject(&p);

	p.input();
}


Game::~Game(){
	taskPool.terminate();
	cout << "Game has ended.\n";
}
