/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmarien <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:26:20 by wmarien           #+#    #+#             */
/*   Updated: 2023/12/06 15:58:44 by wmarien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	change_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
		return (1);
	return (update_envlst("PWD", cwd, false), 0);
}

int	cd_home(void)
{
	char	*home;

	update_envlst("OLDPWD", get_env_val("PWD"), false);
	home = get_env_val("HOME");
	if (!home)
		return (ft_putstr_fd("\033[31m» \033[36mminishell:\033[0;97m", 2),
			ft_putstr_fd("cd: HOME not set\n", 2), 1);
	if (chdir(home) == ENO_SUCCESS)
		return (update_envlst("PWD", home, false), 0);
	return (1);
}

int	cd_err_msg(char *msg)
{
	ft_putstr_fd("\033[31m» \033[36mminishell:\033[0;97m cd: '", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("': no such file or directory\n", 2);
	return (1);
}

int	ms_cd(char *path)
{
	if (!path)
		return (cd_home());
	if (chdir(path) != ENO_SUCCESS)
		return (cd_err_msg(path));
	update_envlst("OLDPWD", get_env_val("PWD"), false);
	return (change_pwd());
}
