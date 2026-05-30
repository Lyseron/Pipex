/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:58:02 by lyaberge          #+#    #+#             */
/*   Updated: 2025/12/30 08:58:02 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// to close fd in case of dup2 error
static void	ft_error_dup(int fd, int *std_w)
{
	close(*std_w);
	close(fd);
	perror("dup2");
	exit(1);
}

// redirect the cmd2 input to the pipe and the output to outfile
void	ft_for_cmd2(t_input i, int *std_r, int *std_w, char **envp)
{
	int		fd;
	char	**tab_cmd2;
	char	*tmp;
	int		status;

	fd = open(i.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_close_fd(std_r, std_w, i.outfile);
	if (dup2(*std_r, 0) == -1)
		ft_close_and_fd(fd, std_r, std_w);
	close(*std_r);
	if (dup2(fd, 1) == -1)
		ft_error_dup(fd, std_w);
	close(fd);
	close(*std_w);
	tab_cmd2 = ft_split(i.cmd2, ' ');
	if (!tab_cmd2)
		exit(1);
	tmp = path(ft_extract_p(envp), tab_cmd2[0], &status);
	ft_exit(&status, tab_cmd2[0], tab_cmd2);
	if (status == 0 && tmp != NULL)
		execve(tmp, tab_cmd2, envp);
	ft_error_execve(tab_cmd2, tmp);
}
