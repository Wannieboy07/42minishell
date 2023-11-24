/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpeeters <lpeeters@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:03:02 by lpeeters          #+#    #+#             */
/*   Updated: 2023/11/24 14:27:25 by lpeeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//check the path of an external command
char	*check_path(char *path)
{
}

//execute external commands
int	exec_ext(char **args)
{
	if (!check_path(args[1]))
		return (0);
}
