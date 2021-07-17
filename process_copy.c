#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<signal.h>

int main(int argc,char ** argv)
{
	if(argc < 3)
	{
		printf("缺少必要命令行参数！\n");
	}

	int processnum = 10;
	if(argv[3] != NULL)
	{
		processnum = atoi(argv[3]);
		if(processnum > 100 || processnum < 0)
		{
			printf("输入的进程数无效！必须于0到100之间\n");
			return 0;
		}
	}

	int everynum;
	int avedatamo;
	int i;
	pid_t pid;
	struct stat st;
	stat(argv[1],&st);
	
	everynum = st.st_size/processnum;
	avedatamo = everynum;
	for(i = 1;i<processnum+1;i++)
	{
		pid = fork();
		if(pid == 0)
			break;
	}
		
	if(pid > 0)
	{
		int countofchildproc = processnum;
		pid_t wpid;
		while(countofchildproc != 0 )
		{

			printf("child process left %d\n",countofchildproc);
			if((wpid = waitpid(-1,NULL,WNOHANG)) > 0 )
			{
				countofchildproc--;	
			}
			usleep(20000);
		}
	}else if(pid == 0)
	{
		if(st.st_size%processnum != 0 && i == processnum)
		everynum = everynum + st.st_size%processnum;
		char strbuf[20];
		sprintf(strbuf, "%s %s %d %d %d %d",argv[1],argv[2],i,everynum,processnum,avedatamo);
		execl("./mycp","mycp",strbuf,NULL);
	}else
	{
		perror("fork error");
	}

	return 0;
}
