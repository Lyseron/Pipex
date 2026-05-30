/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 05:30:27 by lyaberge          #+#    #+#             */
/*   Updated: 2025/12/30 05:30:27 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "libft.h"

// struct for input
typedef struct s_input
{
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;
}	t_input;

// cmd utils
int		ft_pipex(int *std_r, int*std_w);
void	ft_exit(int *status, char *cmd, char **tab);
void	ft_free_split(char **tab);
void	ft_close_fd(int *std_r, int *std_w, char *msg);
void	ft_error_execve(char **tab_cmd1, char *tmp);
void	ft_close_and_fd(int fd, int *std_r, int *std_w);

// cmds
void	ft_for_cmd1(t_input i, int *std_r, int *std_w, char **envp);
void	ft_for_cmd2(t_input i, int *std_r, int *std_w, char **envp);

// path utils
char	*ft_extract_p(char **envp);
int		ft_contain_slash(char *s);
int		ft_access_return(char *path);

// path
char	*path(char *path, char *cmd, int *status);

#endif