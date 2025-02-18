/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:28:32 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/18 19:59:27 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *command, char *envp[])
{
	char	**cmd_token;
	char	*cmd_path;

	cmd_token = ft_split(command, ' ');
	cmd_path = check_addpath_cmd(cmd_token[0], envp);
	execve(cmd_path, cmd_token, envp);
 	perror("execve");
	my_free2d((void **)cmd_token);
	free(cmd_path);
	exit(EXIT_FAILURE);
}


char	*check_addpath_cmd(char *command, char *envp[])
{
	char *path;
	char *path_dir;
	char *cmd_path;
	int	i;

	path = my_getpath(envp);
	path_dir = ft_strtok(path, ":");
	cmd_path = NULL;
	i = 0;
	while (path_dir != NULL)
	{
		cmd_path = ft_strjoin_char(path_dir, command, '/');
		if (access(cmd_path, F_OK | X_OK) != -1)
			(free(cmd_path), my_perr(command, true));
		else
			break ;
		path_dir = ft_strtok(NULL, ":");
	}
	free(path);
	free(path_dir);
	return (cmd_path);
}

char	*my_getpath(char *envp[])
{
	char *path;
	int	i;

	path = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i] + 5;
		i++;
	}
	return(path);
}
