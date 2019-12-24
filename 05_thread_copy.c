#include<stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

typedef struct _info{
	char buf[256];
	int size;
}info;

int main(int argc, char * argv[])
{
	if(argc != 3){
		printf("copy Srcfile target!\n");
		return -1;
	}
	//打开资源文件
	int fd2 = open(argv[2], O_WRONLY);
	int fd1 = open(argv[1], O_RDONLY);
	if(fd1 == -1 || fd2 == -1){
		perror("open error!\n");
		return -1;
	}
	//为资源文件映射区，供给各线程复制
	info * inf = mmap(NULL, sizeof(info),PROT_READ | PROT_WRITE | O_TRUNC, MAP_SHARED, fd1, 0);
	if(inf == MAP_FAILED){
		perror("map error!\n");
		return -1;
	}
	//创建线程
	
	//为每个线程划分工作大小
	//线程开始工作
	//关闭映射区和文件
}
