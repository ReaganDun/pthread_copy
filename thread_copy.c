#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>

typedef struct data
{
	pthread_t tid;
	int nindex;
	int dataamont;
	int everyamont;
	int maxindex;
	char src[1024];
	char des[1024];
}Info;


void * thread_jobs(void *arg)
{
	printf("%ld\n",pthread_self());
	int i = 0;
	Info *info = (Info*)arg;
	off_t offset = (info->nindex)*(info->everyamont);
	int fd = open(info->src,O_RDONLY);
	int dfd = open(info->des,O_RDWR|O_CREAT,0664);
	void *ptr = mmap(NULL,info->dataamont,PROT_READ,MAP_PRIVATE,fd,offset);
	void *dptr = mmap(NULL,info->dataamont,PROT_READ|PROT_WRITE,MAP_SHARED,dfd,offset);
	/*for(i=0;i<info->dataamont;i++)
	{
		((char *)dptr)[i] = ((char *)ptr)[i];
	}*/

	memcpy(dptr,ptr,info->dataamont);
	close(fd);
	close(dfd);
	munmap(ptr,info->dataamont);
	munmap(dptr,info->dataamont);
	pthread_exit(0);
}

int main(int argc,char **argv)
{

	int ncount = 10;
	int i;
	int datam;
	int threadnum;
	int dfd = 0;
	struct stat st;
	stat(argv[1],&st);
	if(argv[3] != 0)
		threadnum = atoi(argv[3]);
	if(threadnum< 100 && threadnum > 0)
		ncount = threadnum;
	datam = st.st_size/ncount;
	dfd = open(argv[2],O_RDWR|O_CREAT,0664);
	ftruncate(dfd,st.st_size);
	close(dfd);


	for(i = 0;i < ncount;i++)
	{
		Info *info = (Info*)malloc(sizeof(Info));
		
		/*info[i].nindex = i;
		strcpy(info[i].src,argv[1]);
		strcpy(info[i].des,argv[2]);
		info[i].everyamont = datam;
		info[i].maxindex = ncount;*/
		info->nindex = i;
		strcpy(info->src,argv[1]);
		strcpy(info->des,argv[2]);
		info->everyamont = datam;
		info->maxindex = ncount;
		
		if(i == ncount-1)
		{
			info->dataamont = datam + st.st_size%datam;
		}
		else 
		{
			info->dataamont = datam;
		}

		pthread_create(&(info->tid),NULL,thread_jobs,(void *)info);
	}

	while(1)
		sleep(1);

	return 0;
}
