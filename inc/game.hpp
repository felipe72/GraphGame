#ifndef GAME_HPP
#define GAME_HPP

#include "enemy.hpp"

class Game{
public:
	Game();
	~Game();
	void start();
	void doAI();
};

#endif