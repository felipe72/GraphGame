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

/* reads from keypress, doesn't echo */
int getch(void){
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

using namespace std;

Game::Game(){}

bool active = true;
char ch = 'o';

char map[10][10];

void printMap(Enemy *e){
	system("clear");
	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			if(e->pos.x == i and e->pos.y == j)
				printf("|e|");
			else
				printf("|%c|", map[i][j]);
		}
		printf("\n");
	}
}

void Game::start(){
	TaskPool taskPool;

	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			map[i][j] = ' ';
		}
	}
	map[4][4] = 'P';

	int x = 4;
	int y = 4;

	Enemy e;
	taskPool.add(std::bind(&Enemy::doAI, &e), 1);
	taskPool.add(std::bind(printMap, &e), 1);

	while(ch!='j'){
		ch = getch();
		int newx=x, newy=y;
		switch(ch){
			case 'w': newx--; break;
			case 's': newx++; break;
			case 'd': newy++; break;
			case 'a': newy--; break;
			case 'o': e.move(0, -1); break;
			case 'p': e.move(0, 1); break;
			case 'j': active = false; taskPool.terminate(); break;
		}
		mutex mx;
		mx.lock();
		map[x][y] = ' ';
		map[newx][newy] = 'P';
		x = newx;
		y = newy;
		mx.unlock();
	}
	// printf("Acabou!\n");
}


Game::~Game(){
	cout << "Game has ended.\n";
}
