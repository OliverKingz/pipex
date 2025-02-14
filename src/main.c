/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:35:09 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/14 22:07:49 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	pid_t	pid;

	(void)argv;
	if (argc != 5)
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2), exit(1);
	check_files(argc, argv, &pipex);
	create_pipes(&pipex);
	pid = fork();
	if (pid == -1)
		(close(pipex.fd[0]), close(pipex.fd[1]), my_perr("fork", true));
	if (pid == 0)
	{
		close(pipex.fd[0]);
		execute_command(argv[2]);
		if (dup2(pipex.fd[1], 1) == -1)
			(close(pipex.fd[1]), my_perr("dup2", true));
		close(pipex.fd[1]); // Cerrar el file descriptor original
		execlp("ls", "ls", "-l", envp);
		perror("execlp");   // Si exec falla
		exit(EXIT_FAILURE); // Terminar el proceso hijo con error
	}
	pid = fork();
	if (pid == -1)
		(close(pipex.fd[0]), close(pipex.fd[1]), my_perr("fork", true));
	if (pid == 0)
	{
		close(pipex.fd[1]);
		if (dup2(pipex.fd[0], 0) == -1)
			(close(pipex.fd[1]), wait(NULL), my_perr("dup2", true));
		close(pipex.fd[0]); // Cerrar el file descriptor original
		execlp("wc", "wc", "-l", NULL);
		perror("execlp");   // Si exec falla
		wait(NULL);         // Esperar al hijo para evitar zombies
		exit(EXIT_FAILURE); // Terminar el proceso padre con error
	}
	wait();
	return (0); // Nunca se alcanza, pero es buena práctica incluirlo
}
