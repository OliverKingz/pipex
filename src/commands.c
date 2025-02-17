/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:28:32 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/17 18:32:57 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char *cmd, int input_fd, int output_fd, char *envp[])
{
	if (dup2(input_fd, 0) == -1 || dup2(output_fd, 1) == -1)
		my_perr("dup2", true);
	close(input_fd);
	close(output_fd);
	execve(cmd, cmd, envp);
	perror("execlp");
	exit(EXIT_FAILURE);
}

void	check_open_files(int argc, char *argv[], t_pipex *pipex)
{
	int	infile;
	int	outfile;

	infile = open(argv[1], O_RDONLY, 644);
	if (infile == -1 || access(argv[1], R_OK) == -1)
		my_perr("input access check", false);
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 644);
	if (outfile == -1)
		my_perr("output open check", true);
	pipex->infile = infile;
	pipex->outfile = outfile;
}

void	create_pipes(t_pipex *pipex)
{
	if (pipe(pipex->fd) == -1)
		my_perr("pipe", true);
}

void	check_commands(int argc, char *argv[], char *envp[])
{
	
}