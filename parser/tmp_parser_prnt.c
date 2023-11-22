#include "../minishell.h"

void	prnt_tabs(int *tabs)
{
	int ctr = 0;

	if (*tabs%2 == 0)
		while(ctr++ != *tabs/2)
			printf("%c", '\t');
	if (*tabs%2 == 1)
		while(ctr++ != *tabs - *tabs/2)
			printf("%c", '\t');
}

void	prnt_args(char **args)
{
	int	i = 0;

	printf("Expanded Args: ");
	while (args[i])
	{
		printf("%s, ", args[i]);
		i++;
	}
	printf("\n");
}

void	prnt_with_io(t_node *node, int *i)
{
	t_io_node	*curr;

	curr = node->io_lst;
	prnt_tabs(i);
	if (*i%2 == 0)
		printf("%i Left\n", *i/2);
	else if (*i%2 == 1)
		printf("%i Right\n", *i - *i/2);
	prnt_tabs(i);
	printf("Type: CMD\t");
	while (curr)
	{
		if (curr->type == IN)
			printf("\t\tType: Input");
		if (curr->type == OUT)
			printf("\t\tType: Output");
		if (curr->type == HERDOC)
			printf("\t\tType: Heredoc");
		if (curr->type == APPEND)
			printf("\t\tType: Append");
		curr = curr->next;
	}
	printf("\n");
	prnt_tabs(i);
	prnt_args(node->exp_args);
	curr = node->io_lst;
	while (curr)
	{
		printf("\t\tValue: %s", curr->value);
		curr = curr->next;
	}
	printf("\n");
}

void	prnt_node(t_node *node, int *i)
{
	if (node->type == P_PIPE)
	{
		prnt_tabs(i);
		printf("%i Left\n", *i/2);
		prnt_tabs(i);
		printf("Type: PIPE\n");
		if (node->left)
		{
			*i += 2;
			prnt_node(node->left, i);
		}
		if (node->right)
		{
			if (*i%2 == 0)
				*i -= 1;
			else
				*i -= 2;
			prnt_node(node->right, i);
		}
	}
	else if (node->type == P_CMD)
	{
		if (node->io_lst)
			prnt_with_io(node, i);
		else
		{
			prnt_tabs(i);
			if (*i%2 == 0)
				printf("%i Left\n", *i/2);
			else if (*i%2 == 1)
				printf("%i Right\n", *i - *i/2);
			prnt_tabs(i);
			printf("Type: CMD\n");
			prnt_tabs(i);
			prnt_args(node->exp_args);
		}
	}
}

void	prnt_ast(t_node	*ast)
{
	int left = 0;

	if (!ast)
	{
		printf("No ast to print\n");
		return ;
	}
	prnt_node(ast, &left);
}
