#include <termios.h>
#include <random>
#include <iostream>
#include <queue>
#include <utility>
#include <cstring>
#include <stack>
#include <climits>
#include <mutex>

#include "enemy.hpp"
#include "taskpool.hpp"
#include "map.hpp"
#include "point.hpp"

using namespace std;
using ii = pair<int, int>;

void Enemy::doAI(){
	if(player->SetEnemiesActive()){
		Point pos_player = player->getPos();
		Point pos_enemy = this->getPos();
		if(movement.empty()){
			int starting = pos_enemy.x*DEFAULT_WIDTH+pos_enemy.y;
			int ending = pos_player.x*DEFAULT_WIDTH+pos_player.y;
			Dijkstra(starting, ending);
		}
		else{
			Direction d = movement.back();
			movement.pop_back();
			switch(d){
				case LEFT: move(0, -1); break;
				case RIGHT: move(0, 1); break;
				case DOWN: move(1, 0); break;
				case UP: move(-1, 0); break;
			}
		}
	}
}

void Enemy::Dijkstra(int s, int t){
	const int MAX = DEFAULT_HEIGHT*DEFAULT_WIDTH;
	stack<Direction> newMovement;

	vector<ii> adjacency_list[MAX];

	for(int i=0; i<MAX; i++){
		if(i >= DEFAULT_WIDTH){
			// Primeira linha
			adjacency_list[i].push_back(ii(1, i-(DEFAULT_WIDTH)));
		}
		if(i <= MAX-DEFAULT_WIDTH){
			// Ultima linha
			adjacency_list[i].push_back(ii(1, i+(DEFAULT_WIDTH)));
		}
		if(i%DEFAULT_WIDTH != 0){
			// Primeira coluna
			adjacency_list[i].push_back(ii(1, i-1));
		}
		if(i%(DEFAULT_WIDTH) !=(DEFAULT_WIDTH-1)  || i == 0){
			// Ultima coluna
			adjacency_list[i].push_back(ii(1, i+1));
		}
	}
	unsigned dist[MAX];
	priority_queue<ii, vector<ii>, greater<ii> > pq;
	pq.push(ii(0, s));
	memset(dist, -1, sizeof dist);
	dist[s] = 0;
	while(not pq.empty() and dist[t] == -1){
		auto p = pq.top();
		pq.pop();

		unsigned d = p.first;
		int u = p.second;
		if(d>dist[u])
			continue;

		for(int i=0; i<adjacency_list[u].size(); i++){
			int v = adjacency_list[u][i].second;
			int w = adjacency_list[u][i].first;
			if(dist[u]+w < dist[v]){
				dist[v] = dist[u]+w;
				pq.push(ii(dist[v],v));
			}
		}
	}
	int u = t;
	while(u != s){
		int minv = INT_MAX;
		int mind = INT_MAX;
		for(int i=0; i<adjacency_list[u].size(); i++){
			int v = adjacency_list[u][i].second;
			if(dist[v] < mind){
				mind = dist[v];
				minv = v;
			}
		}
		int dif = u - minv;

		if(dif == DEFAULT_WIDTH ){
			// Esta a cima
			newMovement.push(DOWN);
		}
		else if(dif == -DEFAULT_WIDTH ){
			// Esta a baixo
			newMovement.push(UP);
		}
		else if(dif == 1){
			// Esta a esquerda
			newMovement.push(RIGHT);
		}
		else if(dif == -1){
			// Esta a direita
			newMovement.push(LEFT);
		}
		u = minv;
	}
	int index = 0;
	Direction *array =(Direction*) malloc(sizeof(Direction) * newMovement.size());
	while(not newMovement.empty()){
		auto a = newMovement.top();
		array[index++] = a;
		movement.push_back(a);
		newMovement.pop();
	}
}