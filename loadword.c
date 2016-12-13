#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ADT_QUEUE.h"
#include "loadword.h"

QUEUE *loadQueue(char *filename, int n) {
	QUEUE *queue = createQueue();
	int fd = open(filename,O_RDONLY);
	int i;
	shufword(filename);
	close(fd);
	fd = open("temp",O_RDONLY);
	for(i=0;i<n;i++) 	
		enqueue(queue,readline(fd));
	return queue;
}

char *readline(int fd) {
	char buf[1024];
	char *ret;
	char ch;
	int i;

	for(i=0;;i++) {
		read(fd,&ch,sizeof(ch));
		if(ch=='\n') {
			buf[i] = '\0';
			break;	
		} else if(isalpha(ch)) {
			buf[i] = ch;	
		} else {
			i--;
		}
	}
	ret = (char*)malloc(sizeof(char)*i+1);
	strcpy(ret,buf);
	return ret;
}

void shufword(char *filename) {
	pid_t pid;

	if((pid=fork())<0) {
		fprintf(stderr,"fork error");
		exit(3);
	}
	
	if(pid == 0) {
		char *av[] = {"shuf",filename};		
		int fd = creat("temp",0644);
		dup2(fd,1);
		execvp(av[0],av);
	} else {
		wait(NULL);
	}
}

void rmtemp() {
	unlink("temp");
}
