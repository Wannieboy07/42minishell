#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	int i = 0;
	char *line = (char*)NULL;

	while (i<5)
	{
		if(line)
		{
			i++;
			free(line);
			line = (char *)NULL;
		}
		line = readline("<tmp>");
		if(line && *line)
			add_history(line);
		printf("Read line:%s\n", line);
	}
	return (0);
}
