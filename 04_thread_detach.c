#include<stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void * thr(void * arg)
{
	printf("I am thread, tid = %lu\n", pthread_self());
	sleep(2);
	printf("sleep end\n");
	return NULL;
}

int main()
{
	pthread_t tid;
	pthread_create(&tid, NULL, thr, NULL);
	pthread_detach(tid);
	sleep(5);
	if(pthread_join(tid, NULL) > 0){
		perror("pthread_join error!\n");
	}
	return 0;
}
