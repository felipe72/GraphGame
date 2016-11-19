#include <new>
#include <iostream>
#include <unistd.h>
#include <mutex>

#include "point.hpp"
#include "map.hpp"

Map::Map(){
	allocate(DEFAULT_HEIGHT, DEFAULT_WIDTH);
}

Map::Map(int height, int width){
	allocate(height, width);
}

Map::~Map(){
	if(m_map != NULL)
		delete(m_map);
}

void Map::allocate(int t_height, int t_width){
	m_height = t_height;
	m_width = t_width;
	m_map = new Tile*[m_height];
	for(int i=0; i<m_height; i++){
		m_map[i] = new Tile[m_width];
	}
}

void Map::clear(){
	system("clear");
	for(int i=0; i<m_height; i++){
		for(int j=0; j<m_width; j++){
			int weight = getWeight(Point(i, j));
			if(weight != 10 && weight != 0){
				addIcon(Point(i, j), 'm', weight);
			}
			else{
				addIcon(Point(i, j), ' ');
			}
		}
	}
}

void Map::addObject(Object *o){
	objects.push_back(o);
}

void Map::addMud(Point p){
	std::mutex mx;
	mx.lock();
	addIcon(p, 'm', 5);
	mx.unlock();
}

void Map::addIcon(Point pos, char icon){
	m_map[pos.x][pos.y].icon = icon;
	m_map[pos.x][pos.y].weight = 10;
}

void Map::addIcon(Point pos, char icon, int weight){
	m_map[pos.x][pos.y].icon = icon;
	m_map[pos.x][pos.y].weight = weight;
}

void Map::print(){
	clear();
	for(unsigned i=0; i<objects.size(); i++){
		addIcon(objects[i]->getPos(), objects[i]->getIcon());
	}
	for(int i=0; i<m_height; i++){
		for(int j=0; j<m_width; j++){
			printf("|%c|", m_map[i][j].icon);
		}
		printf("\n");
	}
}