#include "draw.h"
#include "set_ticker.h"
#include "loadword.h"
#include "ADT_QUEUE.h"
#include <stdio.h>
#include <signal.h>
#include <string.h>

#define BLANK "              "

void checkWord(char *buf);
QUEUE *initBoard();
int addBoard(QUEUE *queue);

typedef struct _board {
	int x;
	int y;
	char *word;
	int flag;
} BOARD;

int i=0;
int score = 0;
int remain;
BOARD board[4][4];
QUEUE *queue;

void play1P() {
	char ch;	
	char buffer[30];
	void handler(int);
	
	i=0;
	score = 0;
	remain = 0;
	clearScreen();
	drawBoard();
	drawPlay();
	refreshScreen();
	inputCursur();
	setCounter(60);
	set_ticker(1000);
	signal(SIGALRM,handler);
	queue = initBoard();

	while(getCounter()>0) {
		ch=getch();
		if(ch=='\n') {
			drawPlay();
			inputCursur();
			buffer[i] = '\0';
			i=0;
			checkWord(buffer);
			drawScore(score);
			inputCursur();
		} else if (ch==0177 || ch == 0010) {
			if(i>0) {
				addch('\b');
				addch(' ');
				addch('\b');
				i--;	
			}
		} else if(isalnum(ch)) {
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
		if(getCounter()%5==0)
			addBoard(queue);
		if(remain==0) {
			score+=5;
			drawScore(score);
		}
		backCursur(i);
		refreshScreen();
	}
}

void checkWord(char *buf) {
	int k;
	for(k=0;k<16;k++) {
		if(strcmp(board[k/4][k%4].word,buf)==0 && board[k/4][k%4].flag == 0) {
			board[k/4][k%4].flag = 1;
			putword(i,BLANK,board[k/4][k%4].y,board[k/4][k%4].x);
			score+=strlen(board[k/4][k%4].word)*5;
			remain--;
			return;
		} 			
	}
	score-=strlen(buf);
}

QUEUE *initBoard() {
	int j;
	QUEUE *queue = loadQueue("wordlist.txt",40);
	for(j=0;j<16;j++) {
		board[j/4][j%4].x = j%4;
		board[j/4][j%4].y = j/4;
		board[j/4][j%4].flag = 1;
		board[j/4][j%4].word = "";
	}
	for(j=0;j<12;j++) {
		board[j/4][j%4].word = dequeue(queue);
		board[j/4][j%4].flag = 0;
		putword(i,board[j/4][j%4].word,j/4,j%4);
		remain++;
	}
	return queue;
}

int addBoard(QUEUE *queue) {
	int j;
	for(j=0;j<16;j++) {
		if(board[j/4][j%4].flag) {
			board[j/4][j%4].word = dequeue(queue);
			board[j/4][j%4].flag = 0;
			putword(i,board[j/4][j%4].word,j/4,j%4);
			remain++;
			return 1;
		}
	}
	return 0;
}

