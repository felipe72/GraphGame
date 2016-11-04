#include <iostream>
#include <functional>
#include <mutex>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>

#include "enemy.hpp"
#include "taskpool.hpp"

void Enemy::doAI(){
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	move(1, 0);
}

void Enemy::move(int t_x, int t_y){
	std::mutex mx;
	mx.lock();
	if(pos.x + t_x > 0 and pos.x + t_x <= 9){
		pos.x += t_x;
	}
	if(pos.y + t_y > 0 and pos.y + t_y <= 9){
		pos.y += t_y;
	}
	mx.unlock();

}