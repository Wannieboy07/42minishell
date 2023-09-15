#include "minishell.h"

void	check_line(char *line)
{
	char *pwd = "pwd";
	char buff[256];

	if (ft_strncmp(line, pwd, ft_strlen(pwd)) == 0)
		getcwd(buff, 256);
	if (*buff)
		printf("%s\n", buff);
}

int main()
{
	int i = 0;
	char *line = (char*)NULL;

	handle_global_signals();
	while (i<5)
	{
		if(line)
		{
			i++;
			free(line);
			line = (char *)NULL;
		}
		line = readline("<tmp> ");
		if(line && *line)
			add_history(line);
//		printf("Read line:%s\n", line);
		check_line(line);
	}
	return (0);
}
