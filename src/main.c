/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:35:09 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/19 21:24:58 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	pid_t	pid[2];
	int		i;

	if (argc != 5)
		(ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2), exit(1));
	check_args(argv);
	init_struct(&pipex);
	pipex.num_cmds = argc - 3;
	create_pipes(&pipex);
	check_open_files(argc, argv, &pipex);
	i = 0;
	while (i < pipex.num_cmds)
	{
		if (i == 0)
			pid[i] = first_execution(i, argv, envp, &pipex);
		if (i == pipex.num_cmds - 1)
			pid[i] = last_execution(i, argv, envp, &pipex);
		i++;
	}
	close(pipex.pd[0]);
	close(pipex.pd[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
// while (waitpid(-1, NULL, 0) > 0);

pid_t	first_execution(int i, char *argv[], char *envp[], t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		(close(pipex->pd[0]), close(pipex->pd[1]), my_perr("fork", true));
	if (pid == 0)
	{
		close(pipex->pd[0]);
		if (dup2(pipex->infile, 0) == -1)
			(close(pipex->infile), close(pipex->pd[1]), my_perr("dup2", true));
		if (dup2(pipex->pd[1], 1) == -1)
			(close(pipex->infile), close(pipex->pd[1]), my_perr("dup2", true));
		(close(pipex->infile), close(pipex->pd[1]));
		execute_command(argv[i + 2], envp);
	}
	return (pid);
}

pid_t	last_execution(int i, char *argv[], char *envp[], t_pipex *pipex)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		(close(pipex->pd[0]), close(pipex->pd[1]), my_perr("fork", true));
	if (pid == 0)
	{
		close(pipex->pd[1]);
		if (dup2(pipex->pd[0], 0) == -1)
			(close(pipex->outfile), close(pipex->pd[0]), my_perr("dup2", true));
		if (dup2(pipex->outfile, 1) == -1)
			(close(pipex->outfile), close(pipex->pd[0]), my_perr("dup2", true));
		(close(pipex->outfile), close(pipex->pd[0]));
		execute_command(argv[i + 2], envp);
	}
	return (pid);
}

void	check_args(char *argv[])
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strlen(argv[i]) == 0)
			(ft_putstr_fd("Error: empty arg\n", 2), exit(1));
		i++;
	}
}

void	check_open_files(int argc, char *argv[], t_pipex *pipex)
{
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		my_perr(argv[argc - 1], true);
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1 || access(argv[1], F_OK | R_OK) == -1)
	{
		my_perr(argv[1], false);
		pipex->infile = open("/dev/null", O_RDONLY);
		if (pipex->infile == -1)
			my_perr("/dev/null", true);
	}
}

void	create_pipes(t_pipex *pipex)
{
	if (pipe(pipex->pd) == -1)
		my_perr("pipe", true);
}
