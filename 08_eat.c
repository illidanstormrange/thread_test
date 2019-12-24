#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

pthread_mutex_t mutex[5];

void * thr_profess(void * arg)
{
	int i = (int)arg;
	int left = 0, right = 0;
	if(i == 4){
		left = 0;
		right = i;
	}
	else {
		left = i;
		right = i + 1;
	}
	while(1){
		pthread_mutex_lock(&mutex[left]);
		if(pthread_mutex_trylock(&mutex[right]) == 0){
			//哲学家抢到了第二个筷子
			printf("哲学家%d号就餐中..., self = %lu\n", i, pthread_self());
			sleep(1);
			printf("哲学家%d号就餐完毕..., self = %lu\n", i, pthread_self());
			pthread_mutex_unlock(&mutex[left]);
			pthread_mutex_unlock(&mutex[right]);
			usleep(2000);
		}
		else {
			//哲学家没有抢到第二个筷子
			pthread_mutex_unlock(&mutex[left]);
		}
	} 
	return NULL;
}

int main()
{
	pthread_t pid[5];
	int i = 0;
	for(; i < 5; i++){
		pthread_mutex_init(&mutex[i], NULL);
	}
	
	for(i = 0; i < 5; i++){
		pthread_create(&pid[i], NULL, thr_profess, i);
	}

	for(i = 0; i < 5; i++){
		pthread_join(pid[i], NULL);
	}

	return 0;
}

