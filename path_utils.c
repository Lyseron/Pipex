/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyaberge <lyaberge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 07:49:58 by lyaberge          #+#    #+#             */
/*   Updated: 2026/01/03 07:49:58 by lyaberge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// parsing of the PATH in the environement
// -> return a line without the "PATH=" with all the paths to be split later
char	*ft_extract_p(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

// check if the cmd contain a slash so is maybe already a real path
int	ft_contain_slash(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

// check the access for the exit 
// -> 0 = succes(exec + exist)
// -> 127 = cmd does not exist
// -> 126 = cmd exist but is not executable
// -> 1 = programme error (exit 1)
int	ft_access_return(char *path)
{
	if (access(path, F_OK) != 0)
		return (127);
	if (access(path, X_OK) != 0)
		return (126);
	return (0);
}
