/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:58:02 by lyaberge          #+#    #+#             */
/*   Updated: 2025/12/30 08:58:02 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_and_fd(int fd, int *std_r, int *std_w)
{
	close(fd);
	ft_close_fd(std_r, std_w, "dup2");
}

// redirect the input for cmd1 to infile and the output to the pipe
// dup2(new_fd, existing_fd) -> new_fd replace existing 
// for the input/output of the cmds
// in the pipe
void	ft_for_cmd1(t_input i, int *std_r, int *std_w, char **envp)
{
	int		fd;
	char	**tab_cmd1;
	char	*tmp;
	int		status;

	fd = open(i.infile, O_RDONLY);
	if (fd == -1)
		ft_close_fd(std_r, std_w, i.infile);
	if (dup2(fd, 0) == -1)
		ft_close_and_fd(fd, std_r, std_w);
	close(fd);
	if (dup2(*std_w, 1) == -1)
		ft_close_fd(std_r, std_w, "dup2");
	close(*std_w);
	close(*std_r);
	tab_cmd1 = ft_split(i.cmd1, ' ');
	if (!tab_cmd1)
		exit(1);
	tmp = path(ft_extract_p(envp), tab_cmd1[0], &status);
	ft_exit(&status, tab_cmd1[0], tab_cmd1);
	if (status == 0 && tmp != NULL)
		execve(tmp, tab_cmd1, envp);
	ft_error_execve(tab_cmd1, tmp);
}
