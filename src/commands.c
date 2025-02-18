/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:28:32 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/18 21:53:58 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *command, char *envp[])
{
	char	**tokenized_cmd;
	char	*path_cmd;

	tokenized_cmd = ft_split(command, ' ');
	if (!tokenized_cmd)
		my_perr("ft_split", true);
	path_cmd = check_addpath_cmd(tokenized_cmd[0], envp);
	if (path_cmd == NULL)
		my_free2d((void **)tokenized_cmd);
	else
	{
		if (execve(path_cmd, tokenized_cmd, envp) == -1)
		{
			my_free2d((void **)tokenized_cmd);
			my_free(path_cmd);
			my_perr("execve", true);
		}
		my_free2d((void **)tokenized_cmd);
		my_free(path_cmd);
	}
}

char	*check_addpath_cmd(char *command, char *envp[])
{
	char	*path;
	char	*path_cmd;

	path = my_getpath(envp);
	path_cmd = my_addpath_cmd(command, path);
	if (path_cmd == NULL)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found", 2);
	}
	return (path_cmd);
}

char	*my_addpath_cmd(char *command, char *path)
{
	char	*path_dir;
	char	*path_cmd;

	path_dir = ft_strtok(path, ":");
	path_cmd = NULL;
	while (path_dir != NULL)
	{
		path_cmd = ft_strjoin_char(path_dir, command, '/');
		if (!path_cmd)
			(perror("malloc"), exit(EXIT_FAILURE));
		if (access(path_cmd, F_OK | X_OK) == 0)
			break ;
		else
		{
			my_free(path_cmd);
			path_dir = ft_strtok(NULL, ":");
		}
	}
	return (path_cmd);
}

char	*my_getpath(char *envp[])
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path);
}
