#include "draw.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

void drawMenu();
void Menu();
void play1P();

int main(void){
	initscr();
	noecho();
	while(1) {
		Menu();
		switch(getchar()) {
			case '1':
				break;
			case '2':
				break;
			case '3':
				endwin();
				exit(1);
			default :
				break;
		}
	}
	endwin();
}


void Menu() {
	clearScreen();
	drawBoard();
	drawMenu();
	refreshScreen();
}

