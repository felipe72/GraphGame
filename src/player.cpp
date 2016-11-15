#include <iostream>
#include <functional>
#include <mutex>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include <vector>

#include "player.hpp"
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

void Player::input(){
	char ch;
	bool active = true;
	while(ch!='j' and active){
		ch = getch();
		switch(ch){
			case 'j': active = false; break;
			case 'a': move(0, -1); break;
			case 'd': move(0, 1); break;
			case 's': move(1, 0); break;
			case 'w': move(-1, 0); break;
			case 'p': setEnemiesActive = true; break;
		}
	}
}
