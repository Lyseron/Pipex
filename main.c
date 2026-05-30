/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 05:30:14 by lyaberge          #+#    #+#             */
/*   Updated: 2025/12/30 05:30:14 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// create the pipe 3 and 4
// to after be dup2 with the existing one stdin = 0 / stdout = 1
int	ft_pipex(int *std_r, int*std_w)
{
	int	std[2];

	if (pipe(std) == -1)
		return (0);
	*std_r = std[0];
	*std_w = std[1];
	return (1);
}

// wait for cmd1 and cmd2 to avoid zombies
// check the exit code for cmd2 and return the right exit
int	ft_wait(pid_t pid_1, pid_t pid_2)
{
	int	status1;
	int	status2;
	int	code_exit;

	if (waitpid(pid_1, &status1, 0) == -1)
		return (1);
	if (waitpid(pid_2, &status2, 0) == -1)
		return (1);
	if (WIFEXITED(status2))
		code_exit = WEXITSTATUS(status2);
	else if (WIFSIGNALED(status2))
		code_exit = 128 + WTERMSIG(status2);
	else
		code_exit = 1;
	return (code_exit);
}

void	ft_init_struct(t_input *i, char *argv[])
{
	i->infile = argv[1];
	i->cmd1 = argv[2];
	i->cmd2 = argv[3];
	i->outfile = argv[4];
}

// create the children process
int	main(int argc, char *argv[], char **envp)
{
	t_input	i;
	pid_t	pid_1;
	pid_t	pid_2;
	int		std_r;
	int		std_w;

	if (argc != 5)
		return (1);
	ft_init_struct(&i, argv);
	if (ft_pipex(&std_r, &std_w) == 0)
		return (perror("pipe"), 1);
	pid_1 = fork();
	if (pid_1 == -1)
		return (perror("pid_1"), 1);
	else if (pid_1 == 0)
		ft_for_cmd1(i, &std_r, &std_w, envp);
	pid_2 = fork();
	if (pid_2 == -1)
		return (perror("pid_2"), 1);
	else if (pid_2 == 0)
		ft_for_cmd2(i, &std_r, &std_w, envp);
	close(std_r);
	close(std_w);
	return (ft_wait(pid_1, pid_2));
}
