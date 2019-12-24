#include<stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int g_num = 100;


typedef struct _pro{
	int num;
	struct _pro *next;
}pro;

pro *head = NULL;

void * thr_producter(void * arg)
{
	while(1){
		pthread_mutex_lock(&mutex);
		//printf("a\n");
		pro * p = malloc(sizeof(pro));
	//	printf("b\n");
		p->num = g_num++;
		p->next = head;
		printf("%s, self = %lu, num = %d\n", __FUNCTION__, pthread_self(), p->num);
	//	printf("c\n");
		head = p;
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&cond);
		sleep(rand() % 2);
	}
	return NULL;
}

void * thr_customer(void * arg)
{
	pro* p =NULL;
	while(1){
		pthread_mutex_lock(&mutex);
		if(head == NULL){
			pthread_cond_wait(&cond, &mutex);
		}
	//	printf("d\n");
	//	printf("f\n");
		p = head;
		head = head->next;
		printf("%s, self = %lu, num = %d\n", __FUNCTION__, pthread_self(), p->num);
		free(p);
		pthread_mutex_unlock(&mutex);
	//	printf("e\n");
		sleep(rand() % 5);
	}
	return NULL;
}

int main()
{
	pthread_t tid[3];
	pthread_create(&tid[0], NULL, thr_producter, NULL);
	pthread_create(&tid[1], NULL, thr_customer, NULL);
	pthread_create(&tid[2], NULL, thr_customer, NULL);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	return 0;
}
