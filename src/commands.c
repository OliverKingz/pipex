/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:28:32 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/21 23:45:10 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *command, char *envp[], t_pipex *pipex)
{
	char	**tokenized_cmd;
	char	*path_cmd;

	tokenized_cmd = ft_split(command, ' ');
	if (!tokenized_cmd)
		(close_fds(pipex), my_perr("ft_split", true));
	path_cmd = check_addpath_cmd(tokenized_cmd[0], envp, pipex);
	if (execve(path_cmd, tokenized_cmd, envp) == -1)
	{
		close_fds(pipex);
		my_free2d((void **)tokenized_cmd);
		exit(ERR_CMD_NOT_FOUND);
	}
	my_free2d((void **)tokenized_cmd);
	my_free(path_cmd);
}

pid_t	first_execution(int i, char *argv[], char *envp[], t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		(close_fds(pipex), my_perr("fork", true));
	if (pid == 0)
	{
		close(pipex->pd[0]);
		if (dup2(pipex->infile, 0) == -1)
			(close_fds(pipex), my_perr("dup2", true));
		if (dup2(pipex->pd[1], 1) == -1)
			(close_fds(pipex), my_perr("dup2", true));
		(close(pipex->infile), close(pipex->pd[1]));
		execute_command(argv[i + 2], envp, pipex);
	}
	return (pid);
}

pid_t	last_execution(int i, char *argv[], char *envp[], t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		(close_fds(pipex), my_perr("fork", true));
	if (pid == 0)
	{
		close(pipex->pd[1]);
		if (dup2(pipex->pd[0], 0) == -1)
			(close_fds(pipex), my_perr("dup2", true));
		if (dup2(pipex->outfile, 1) == -1)
		{
			if (pipex->outfile == -1)
				(close_fds(pipex), exit(EXIT_FAILURE));
			(close_fds(pipex), my_perr("dup2", true));
		}
		(close(pipex->outfile), close(pipex->pd[0]));
		execute_command(argv[i + 2], envp, pipex);
	}
	return (pid);
}
