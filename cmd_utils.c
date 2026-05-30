/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:58:02 by lyaberge          #+#    #+#             */
/*   Updated: 2025/12/30 08:58:02 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// free all the string in *tab and the tab
void	ft_free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// handle the error msg and exit for the fail path
void	ft_exit(int *status, char *cmd, char **tab)
{
	if (*status == 127)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found", 19);
		write(2, "\n", 1);
		ft_free_split(tab);
		exit(127);
	}
	else if (*status == 126)
	{
		perror(cmd);
		ft_free_split(tab);
		exit(126);
	}
	else if (*status == 1)
	{
		ft_free_split(tab);
		exit(1);
	}
}

// handle the close for the fd
void	ft_close_fd(int *std_r, int *std_w, char *msg)
{
	close(*std_r);
	close(*std_w);
	perror(msg);
	exit(1);
}

// handle the error of execve
void	ft_error_execve(char **tab_cmd1, char *tmp)
{
	perror(tab_cmd1[0]);
	ft_free_split(tab_cmd1);
	free(tmp);
	exit(1);
}
