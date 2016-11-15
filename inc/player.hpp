#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "object.hpp"
#include "point.hpp"

class Player : public Object{
	public:
	Player() : Object('p') {}
	Player(Point t_pos) : Object(t_pos, 'p') {}
	void input();
	bool SetEnemiesActive(){return setEnemiesActive;}

private:
	bool setEnemiesActive = false;
};

#endif