#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main()
{
	char *cmd = NULL;
	ssize_t ret;
	size_t len;
	int length;
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
		else
		{
			printf("%s: command not fount\n",cmd);
			continue;
		}
	}
	return 0;
}