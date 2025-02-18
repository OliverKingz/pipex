/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:35:09 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/18 17:25:30 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strlen(argv[i]) == 0)
			ft_putstr_fd("Error: empty arg", 2), exit(1);
		i++;
	}
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

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	pid_t	pid;

	if (argc != 5)
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2), exit(1);
	check_args(argc, argv);
	check_open_files(argc, argv, &pipex);
	// create_pipes(&pipex);
	// pid = fork();
	// if (pid == -1)
	// 	(close(pipex.fd[0]), close(pipex.fd[1]), my_perr("fork", true));
	// if (pid == 0)
	// {
	// 	close(pipex.fd[0]);
	// 	execute_command(argv[2], pipex.infile, pipex.fd[0]);
	// }
	// wait(NULL);
	// pid = fork();
	// if (pid == -1)
	// 	(close(pipex.fd[0]), close(pipex.fd[1]), my_perr("fork", true));
	// if (pid == 0)
	// {
	// 	close(pipex.fd[1]);
	// 	execute_command(argv[argc - 2], pipex.fd[0], pipex.outfile);
	// }
	// wait(NULL);
	return (0); // Nunca se alcanza, pero es buena práctica incluirlo
}
