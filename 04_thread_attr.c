#include<stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void * thr(void * arg)
{
	printf("I am a thread, tid = %lu\n", pthread_self());
	return NULL;
}

int main()
{
	//初始化线程状态
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	//将线程设置为分离态
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	
	pthread_t tid;
	//此时创建的线程状态为分离态
	pthread_create (&tid, &attr, thr, NULL);
	if(pthread_join(tid, NULL) > 0){
		perror("thread join error!\n");
	}

	pthread_attr_destroy(&attr);
	return 0;
}
