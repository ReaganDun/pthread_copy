#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#define MAXNUM 8192
int copy_file(const char *sfile,const char * dfile,const char * order,const char * dataamount,const char * maxnumofproc)
{
	FILE *sfd;
	FILE *dfd;
	int order = atoi(order);
	int dataamo = atoi(dataamount);
	int maxnumproc = atoi(maxnumofproc);
	int rsize;
	int sizeofdata = atoi(dataamount);
	char buffer[MAXNUM];
	int wsize;
	if(((sfd = fopen(sfile,"r")) != NULL) && ((dfd = fopen(dfile,"a")) != NULL))
	{
		if(order != maxnumproc)
		{
			fseek(sfd,(order-1)*dataamo,SEEK_SET);
			fseek(dfd,(order-1)*dataamo,SEEK_SET);
		}
		else if(order == maxnumproc)
		{
			fseek(sfd,-dataamo,SEEK_END);
			fseek(dfd,dataamo,SEEK_CUR);
		}
		fread(buffer,1,dataamo,sfd)	
		fwrite(buffer,1,dataamo,dfd);
	}
	if(rsize == 0)
	{	
		fclose(sfd);
		fclose(dfd);
	}
	return 0;
}

int main(int argc,char **argv)
{
	int test_var1 = 200;
	int test_var2 = 300;
	if(argc < 6)printf("error!/n\n");
	if((access(argv[1],F_OK))!=0)
	{
		printf("%s not exists!/n\n",argv[1]);
		exit(0);
	}
	copy_file(argv[1],argv[2],argv[3],argv[4],argv[5]);

	return 0;
}
