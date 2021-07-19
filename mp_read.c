/*读端*/
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
	int rfd = open("mfile",O_RDWR);
	int size = sizeof(GInfo);
	GInfo * ptr;
	ptr = mmap(NULL,size,PROT_READ,MAP_SHARED,rfd,0);
	close(rfd);
	while(1)
	{
		printf("%s %d %s",ptr->GName,ptr->GPric,ptr->GDesc);
		sleep(2);
	}
	return 0;
}
