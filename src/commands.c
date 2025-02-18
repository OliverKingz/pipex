/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:28:32 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/18 17:36:30 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	execute_command(char *cmd, int input_fd, int output_fd, char *envp[])
// {
// 	if (dup2(input_fd, 0) == -1 || dup2(output_fd, 1) == -1)
// 		my_perr("dup2", true);
// 	close(input_fd);
// 	close(output_fd);
// 	execve(cmd, cmd, envp);
// 	perror("execve");
// 	exit(EXIT_FAILURE);
// }

void	execute_command(int index, char *argv[], char *envp[], t_pipex *pipex)
{
	char	**cmd_token;
	char	*cmd_path;

	cmd_token = ft_split(argv[index], ' ');
	cmd_path = check_addpath_cmd(cmd_token[0]);
	execve(cmd_path, cmd_token, envp);
 	perror("execve");
	my_free2d(cmd_token);
	free(cmd_path);
	exit(EXIT_FAILURE);
}


char	*check_addpath_cmd(char *command, char *envp[])
{
	char *path;
	char *path_dir;
	int	i;

	path = my_getpath(envp);
	path_dir = ft_strtok(path, ":");
	i = 0;
	while (path_dir != NULL)
	{
		path_dir = ft_strtok(path, ":");
	}
	free(path);
	free(path_dir);
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
