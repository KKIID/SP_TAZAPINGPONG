#include <curses.h>
#include "draw.h"

void drawBoard() {
	int i;
	for(i=0;i<COLS;i++)
		addstr("*");
	for(i=0;i<LINES;i++){
		move(i,0);
		addstr("*");
		move(i,COLS-1);
		addstr("*");	
	}
	move(LINES-1,0);
	for(i=0;i<COLS-1;i++)
		addstr("*");
}

void drawMenu() {
	move(LINES/3,COLS/2-12);
	addstr("T A Z A P I N G - P O N G");
	move(LINES/2+1,COLS/2-12);
	addstr("*************************");
	move(LINES/2+2,COLS/2-12);
	addstr("*    1. Play Game[1P]   *");
	move(LINES/2+3,COLS/2-12);
	addstr("*    2. Play Game[2P]   *");
	move(LINES/2+4,COLS/2-12);
	addstr("*    3. EXIT            *");
	move(LINES/2+5,COLS/2-12);
	addstr("*************************");
	initCursur();
}

void drawPlay() {
	move(LINES/6*5-1,COLS/2-18);
	addstr("*                                    *");
	move(LINES/6*5,COLS/2-18);
	addstr(" ************************************ ");
}

void initScreen() {
	initscr();
}

void clearScreen() {
	clear();
}

void refreshScreen() {
	refresh();
}

void initCursur() {
	move(LINES-1,COLS-1);
}

void inputCursur() {
	move(LINES/6*5-1,COLS/2-17);
}

void backCursur(int i) {
	move(LINES/6*5-1,COLS/2-17 + i);
}

void timerCursur() {
	move(2,COLS-5);
}

