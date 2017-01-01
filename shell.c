#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

char arg_list[10][10];
int getcmd(char*);
int spawn(char*,char**);
int main()
{
	char *cmd = NULL;
	ssize_t ret;
	size_t len;
	int length;
	int i,j;
	while(1)
	{
		printf("$0 ");
		ret = getline(&cmd,&len,stdin);
		if(ret == -1)
		{
			break;
		}
		cmd[ret - 1] = '\0';
		if(strcmp("pwd",cmd) == 0)
		{
			char buf[50];
			getcwd(buf,sizeof(buf));
			printf("%s\n",buf);
		}
		else if(strcmp("exit",cmd) == 0)
		{
			break;
		}
		else if((ret = getcmd(cmd)) == 0)
		{
			for(i=0;i<10;i++)
				printf("%s ",arg_list[i]);
			printf("\n");
			//spawn(cmd,arg_list);
		}
		else
		{
			printf("%s: command not fount\n",cmd);
			continue;
		}
		memset(cmd,'\0',sizeof(cmd));
	}
	return 0;
}
int getcmd(char *cmd)
{
	int i=0,j=0,k=0;
	int flag = 0;
	char command[20];
	char temp[10][10];
	while(cmd[i]!= '\0')
	{
		if(cmd[i] != ' ' && flag == 0)
		{
			arg_list[k][j] = cmd[i];
			command[j++] = cmd[i];
		}
		else if(cmd[i]==' ' && flag ==0 )
		{
			command[j]='\0';
			arg_list[k][j]='\0';
			j = 0;
			flag = 1;
			k++;
		}
		else if(cmd[i] != ' ' && flag == 1)
		{
			arg_list[k][j++] = cmd[i];

		}
		else if(cmd[i] == ' ' && flag ==1 )
		{
			arg_list[k][j] = '\0';
			j =0;
			k++;
		}
		i++;
	}
	if(flag == 0)
	{
		command[j] = '\0';
	}
	if(flag == 1 )
	{
		arg_list[k][j] = '\0';
	}
	for(i = k+1;i<10;i++)
	{
		for(j =0;j<10;j++)
			arg_list[k][j] = '\0';
	}
	memcpy(cmd,command,sizeof(command));
	return 0;
}
int spawn(char* cmd,char** arg_list)
{
	pid_t child;
	child = fork();
	if(child != 0)
	{
		return child;
	}
	else
	{
		execvp(cmd,arg_list);
		fprintf(stderr,"spawn error\n");
		return -1;
	}
}