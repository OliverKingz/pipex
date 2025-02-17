/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:35:09 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/17 18:12:56 by ozamora-         ###   ########.fr       */
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
