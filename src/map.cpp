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
	m_map = new char*[m_height];
	for(int i=0; i<m_height; i++){
		m_map[i] = new char[m_width];
	}
}

void Map::clear(){
	system("clear");
	for(int i=0; i<m_height; i++){
		for(int j=0; j<m_width; j++){
			m_map[i][j] = ' ';
		}
	}
}

void Map::addObject(Object *o){
	objects.push_back(o);
}

void Map::addIcon(Point pos, char icon){
	m_map[pos.x][pos.y] = icon;
}

void Map::print(){
	clear();
	for(unsigned i=0; i<objects.size(); i++){
		addIcon(objects[i]->getPos(), objects[i]->getIcon());
	}
	for(int i=0; i<m_height; i++){
		for(int j=0; j<m_width; j++){
			printf("|%c|", m_map[i][j]);
		}
		printf("\n");
	}
}