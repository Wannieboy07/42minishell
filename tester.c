#include<stdio.h>
#include <stdlib.h>
#include<unistd.h>

int main(int argc, char **argv, char **env)
{
	int i=0;

	(void)argc;
	(void)argv;
	while (env[i])
		printf("%s\n",env[i++]);
/*	while (1)
	{
		printf("PID:%d\n", getpid());
		printf("Waisting rescources...\n");
		sleep(2);
	}
*/
	return (0);
}
