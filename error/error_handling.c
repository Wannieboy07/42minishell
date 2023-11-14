/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:14:04 by wmarien           #+#    #+#             */
/*   Updated: 2023/11/14 18:52:21 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//print errors
int	prnt_err(char *str, char **av)
{
	int	i;

	printf(RED "Error" GREY ": ");
	if (str)
		printf("%s", str);
	if (str && av)
		printf(": ");
	if (av)
	{
		printf("run %s without arguments\n", av[0]);
		printf("Tip: change '");
		i = 0;
		while (av[i + 1])
			printf("%s ", av[i++]);
		printf("%s' to '%s'", av[i], av[0]);
	}
	printf("\n");
	return (1);
}
