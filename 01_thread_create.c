#include<stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void * thr(void * arg)
{
	printf("I am a thread, pid = %d, threadid = %lu\n", getpid(), pthread_self());
	pthread_exit(NULL);
}

int main()
{
	pthread_t pid;
	pthread_create(&pid, NULL, thr, NULL);
	printf("I am a main thead, pid = %d, threadid = %lu\n", getpid(), pthread_self());
	pthread_exit(NULL);
	return 0;
}
