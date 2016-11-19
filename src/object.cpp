#include <mutex>

#include "object.hpp"
#include "map.hpp"

void Object::move(int t_x, int t_y){
	std::mutex mx;
	mx.lock();
	if(pos.x + t_x >= 0 and pos.x + t_x <= DEFAULT_WIDTH){
		pos.x += t_x;
	}
	if(pos.y + t_y >= 0 and pos.y + t_y <= DEFAULT_HEIGHT){
		pos.y += t_y;
	}
	mx.unlock();

}