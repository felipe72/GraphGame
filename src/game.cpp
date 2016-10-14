#include <iostream>
#include <functional>
#include <mutex>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#include "game.hpp"
#include "tile.hpp"
#include "taskpool.hpp"

/* reads from keypress, doesn't echo */
int getch(void)
{
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

	// cout << "Game has started." << endl;	
	
	taskPool.add(std::bind(&Game::doAI, this, 0, 0), 1);
	taskPool.add(std::bind(&Game::doAI, this, 1, 1), 1);
	taskPool.add(std::bind(&Game::doAI, this, 2, 3), 1);
	taskPool.add(std::bind(&Game::doAI, this, 6, 6), 1);

	while(ch!='j'){
		ch = getch();
		int newx=x, newy=y;
		switch(ch){
			case 'w': newx--; break;
			case 's': newx++; break;
			case 'd': newy++; break;
			case 'a': newy--; break;
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

void printMap(){
	system("clear");
	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			printf("|%c|", map[i][j]);
		}
		printf("\n");
	}
}

void Game::doAI(int t_i, int t_j){
	int i=t_i, j=t_j, k=0;
	while(active){
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		k = (k+1)%100;
		if(k==0){
			i++;
			if(i>9){
				i=0;
				j++;
			}
			if(j>9){
				i=0;
				j=0;
			}
			mutex mx;
			mx.lock();
			if(map[i][j] == 'P'){
				printMap();
				break;
			}
			map[i][j] = 'E';
			printMap();
			map[i][j] = ' ';
			mx.unlock();
		}
	}
}

Game::~Game(){
	cout << "Game has ended.\n";
}
