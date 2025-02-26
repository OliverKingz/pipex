/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:55:11 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/26 01:24:49 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	execute_command(char *command, char *envp[], t_pipex *pipex)
{
	char	**tokenized_cmd;
	char	*path_cmd;

	tokenized_cmd = ft_split(command, ' ');
	if (!tokenized_cmd)
		(clean(pipex), my_perr("ft_split", true));
	path_cmd = check_addpath_cmd(tokenized_cmd[0], envp, pipex);
	if (!path_cmd)
	{
		clean(pipex);
		my_free2d((void **)tokenized_cmd);
		exit(ERR_CMD_NOT_FOUND);
	}
	if (execve(path_cmd, tokenized_cmd, envp) == -1)
	{
		clean(pipex);
		my_free2d((void **)tokenized_cmd);
		my_free(path_cmd);
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
		(clean(pipex), my_perr("fork", true));
	if (pid == 0)
	{
		close(pipex->pipe_fd[0]);
		if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
			(clean(pipex), my_perr("dup2", true));
		if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
			(clean(pipex), my_perr("dup2", true));
		(close(pipex->in_fd), close(pipex->pipe_fd[1]));
		execute_command(argv[i + 2], envp, pipex);
	}
	close(pipex->pipe_fd[1]);
	pipex->prev_pipe_fd = pipex->pipe_fd[0];
	return (pid);
}

pid_t	last_execution(int i, char *argv[], char *envp[], t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		(clean(pipex), my_perr("fork", true));
	if (pid == 0)
	{
		close(pipex->pipe_fd[1]);
		if (dup2(pipex->prev_pipe_fd, STDIN_FILENO) == -1)
			(clean(pipex), my_perr("dup2", true));
		if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
		{
			if (pipex->out_fd == -1)
				(clean(pipex), exit(EXIT_FAILURE));
			(clean(pipex), my_perr("dup2", true));
		}
		(close(pipex->out_fd), close(pipex->prev_pipe_fd));
		close_fds(pipex);
		execute_command(argv[i + 2 + pipex->here_doc], envp, pipex);
	}
	close(pipex->prev_pipe_fd);
	return (pid);
}

pid_t	middle_execution(int i, char **argv, char *envp[], t_pipex *pipex)
{
	pid_t	pid;

	if (pipe(pipex->pipe_fd) == -1)
		(clean(pipex), my_perr("pipe", true));
	pid = fork();
	if (pid == -1)
		(clean(pipex), my_perr("fork", true));
	if (pid == 0)
	{
		close(pipex->pipe_fd[0]);
		if (dup2(pipex->prev_pipe_fd, STDIN_FILENO) == -1)
			(clean(pipex), my_perr("dup2", true));
		if (dup2(pipex->pipe_fd[1], STDOUT_FILENO) == -1)
			(clean(pipex), my_perr("dup2", true));
		close(pipex->prev_pipe_fd);
		close(pipex->pipe_fd[1]);
		execute_command(argv[i + 2 + pipex->here_doc], envp, pipex);
	}
	close(pipex->prev_pipe_fd);
	close(pipex->pipe_fd[1]);
	pipex->prev_pipe_fd = pipex->pipe_fd[0];
	return (pid);
}
