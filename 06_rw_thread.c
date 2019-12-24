#include<stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
int num = 0;

void * thr_write(void * arg)
{
	while(1){
		pthread_rwlock_rdlock(&rwlock);
		printf("%s, self = %lu, num = %d\n",__FUNCTION__, pthread_self(), ++num);
		usleep(1000);
		pthread_rwlock_unlock(&rwlock);
		usleep(1000);
	}
	return NULL;
}

void * thr_read(void * arg)
{
	while(1){
		pthread_rwlock_wrlock(&rwlock);
		printf("%s, self = %lu, num = %d\n",__FUNCTION__, pthread_self(), num);
		usleep(1000);
		pthread_rwlock_unlock(&rwlock);
		usleep(1000);
	}
	return NULL;
}

int main()
{
	int i = 0;
	pthread_t tid[4];
	for(; i < 2; i++){
		tid[i] = pthread_create(&tid[i], NULL, thr_write, NULL);
	}
	for(; i < 4; i++){
		tid[i] = pthread_create(&tid[i], NULL, thr_read, NULL);
	}
	for(i = 0; i < 4; i++){
		pthread_join(tid[i], NULL);
	}
	while(1);
	return 0;
}
