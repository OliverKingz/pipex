/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:28:32 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/14 22:08:15 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd, int input_fd, int output_fd, char *envp[])
{
	if (dup2(input_fd, 0) == -1 || dup2(output_fd, 1) == -1)
		my_perr("dup2", true);
	close(input_fd);
	close(output_fd);
	execlp(cmd, cmd, envp);
	perror("execlp");
	wait(NULL);
	exit(EXIT_FAILURE);
}

void	check_files(int argc, char *argv[], t_pipex *pipex)
{
	int	infile;
	int	outfile;

	if (access(argv[1], R_OK) == -1)
		my_perr("input access check", true);
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 644);
	if (outfile == -1) {
		my_perr("output open check", true);
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
}

void	create_pipes(t_pipex *pipex)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		my_perr("pipe", true);
	pipex->fd[0] = pipe_fd[0];
	pipex->fd[1] = pipe_fd[1];
}
