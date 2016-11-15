#include <iostream>
#include <functional>
#include <mutex>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>

#include "game.hpp"
#include "tile.hpp"
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
	enemies.push_back(Enemy(Point(0, 0), &p, &map));
	// Enemy e2(Point(0, 0), &p, &map);
	// Enemy e3(Point(0, 0), &p, &map);
	// Enemy e4(Point(0, 0), &p, &map);
	for(Enemy e : enemies){
		map.addObject(&e);
		taskPool.add(std::bind(&Enemy::doAI, &e), 1);
	}
	map.addObject(&p);
	// map.addObject(&e2);
	// map.addObject(&e3);
	// map.addObject(&e4);
	// taskPool.add(std::bind(&Enemy::doAI, &e2), 1);
	// taskPool.add(std::bind(&Enemy::doAI, &e3), 1);
	// taskPool.add(std::bind(&Enemy::doAI, &e4), 1);

	p.input();
}


Game::~Game(){
	taskPool.terminate();
	cout << "Game has ended.\n";
}
