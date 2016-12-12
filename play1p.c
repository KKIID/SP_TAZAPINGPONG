#include "draw.h"
#include "set_ticker.h"
#include <stdio.h>
#include <signal.h>

int i=0;

void play1P() {
	char ch;
	
	char buffer[30];
	void handler(int);
	
	i=0;
	clearScreen();
	drawBoard();
	drawPlay();
	refreshScreen();
	inputCursur();
	setCounter(60);
	set_ticker(1000);
	signal(SIGALRM,handler);

	while(true) {
		ch=getch();
		if(ch=='\n') {
			drawPlay();
			inputCursur();
			buffer[i] = '\0';
			i=0;
			inputCursur();
		} else {
			addch(ch);
			buffer[i] = ch;
			i++;
		}
		refreshScreen();
	}
}

void handler(int s) {
	if(getCounter()>=0) {
		timerCursur();
		addstr(getCounter2());
		setCounter(getCounter()-1);
		backCursur(i);
		refreshScreen();
	}
}

