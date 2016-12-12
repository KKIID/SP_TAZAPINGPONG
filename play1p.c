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

	while(getCounter()>0) {
		ch=getch();
		if(ch=='\n') {
			drawPlay();
			inputCursur();
			buffer[i] = '\0';
			i=0;
			inputCursur();
		} else if (ch==0177 || ch == 0010) {
			if(i>0) {
				addch('\b');
				addch(' ');
				addch('\b');
				i--;	
			}
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

