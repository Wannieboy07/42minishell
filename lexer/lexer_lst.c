#include "../minishell.h"

t_token	*new_token(t_tokentype type, char *value)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	return (new_token);
}

void	token_add_back(t_token **head, t_token *new_node)
{
	t_token	*curr_node;

	if (!*head)
	{
		*head = new_node;
		return ;
	}
	curr_node = *head;
	while (curr_node && curr_node -> next)
		curr_node = curr_node -> next;
	curr_node->next = new_node;
	new_node->prev = curr_node;
}

void	free_token_lst(t_token **head)
{
	t_token	*curr_node;
	t_token	*next;

	curr_node = *head;
	if (!curr_node)
		return;
	while (curr_node)
	{
		free(curr_node->value);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*head = NULL;
}
