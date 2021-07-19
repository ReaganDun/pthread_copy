#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/mman.h>

typedef struct GStr
{
	char GName[10];
	int GPric;
	char GDesc[256];
}GInfo;


int main()
{
	int wfd = open("mfile",O_RDWR|O_CREAT,0664);
	int size = sizeof(GInfo);
	ftruncate(wfd,size);
	GInfo * ptr = NULL;
	ptr = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,wfd,0);
	close(wfd);

	ptr->GPric = 100;
	while(1)
	{
		sprintf(ptr->GName,"MIHAYO");
		ptr->GPric+=10;
		sprintf(ptr->GDesc,"开放世界RPG");
		sleep(2);
	}

	munmap(ptr,size);
	return 0;
}
