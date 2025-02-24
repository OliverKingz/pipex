/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:55:11 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/24 21:56:40 by ozamora-         ###   ########.fr       */
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
		close(pipex->pipe_fd[0][0]);
		if (dup2(pipex->infile_fd, STDIN_FILENO) == -1)
			(clean(pipex), my_perr("dup2", true));
		if (dup2(pipex->pipe_fd[0][1], STDOUT_FILENO) == -1)
			(clean(pipex), my_perr("dup2", true));
		(close(pipex->infile_fd), close(pipex->pipe_fd[0][1]));
		execute_command(argv[i + 2], envp, pipex);
	}
	return (pid);
}

pid_t	last_execution(int i, char *argv[], char *envp[], t_pipex *pipex)
{
	pid_t	pid;
	int		read_pipe;
	int		write_pipe;

	read_pipe = (i - 1) % 2;
	write_pipe = i % 2;
	pid = fork();
	if (pid == -1)
		(clean(pipex), my_perr("fork", true));
	if (pid == 0)
	{
		close(pipex->pipe_fd[read_pipe][1]);
		if (dup2(pipex->pipe_fd[read_pipe][0], STDIN_FILENO) == -1)
			(clean(pipex), my_perr("dup2", true));
		if (dup2(pipex->outfile_fd, STDOUT_FILENO) == -1)
		{
			if (pipex->outfile_fd == -1)
				(clean(pipex), exit(EXIT_FAILURE));
			(clean(pipex), my_perr("dup2", true));
		}
		(close(pipex->outfile_fd), close(pipex->pipe_fd[read_pipe][0]));
		close_fds(pipex);
		execute_command(argv[i + 2], envp, pipex);
	}
	return (pid);
}
pid_t	middle_execution(int i, char **argv, char *envp[], t_pipex *pipex)
{
	pid_t	pid;
	int		read_pipe;
	int		write_pipe;

	read_pipe = (i - 1) % 2;
	write_pipe = i % 2;
	pid = fork();
	if (pid == -1)
		(clean(pipex), my_perr("fork", true));
	if (pid == 0)
	{
		close(pipex->pipe_fd[read_pipe][1]);
		close(pipex->pipe_fd[write_pipe][0]);
		if (dup2(pipex->pipe_fd[read_pipe][0], STDIN_FILENO) == -1)
			(clean(pipex), my_perr("dup2", true));
		if (dup2(pipex->pipe_fd[write_pipe][1], STDOUT_FILENO) == -1)
			(clean(pipex), my_perr("dup2", true));
		close(pipex->pipe_fd[read_pipe][0]);
		close(pipex->pipe_fd[write_pipe][1]);
		execute_command(argv[i + 2], envp, pipex);
	}
	return (pid);
}
