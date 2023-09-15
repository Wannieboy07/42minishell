
#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"


/*=== Signal Handling ===*/

void	handle_global_signals(void);
void	handle_cmd_signals(void);

#endif
