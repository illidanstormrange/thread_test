#include<stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void * thr(void * arg)
{
	printf("I am thread, tid = %lu\n", pthread_self());
	
	//pthread_exit(NULL);
	return (void *)100;
}

int main()
{
	pthread_t tid;
	pthread_create(&tid, NULL, thr, NULL);
	printf("I am main thread,\n");
	void *ret;
	pthread_join(tid, &ret);
	printf("thread has been exit with %d\n", (int)ret);
	pthread_exit(NULL);
}
