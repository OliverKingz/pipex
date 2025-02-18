/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:35:09 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/18 20:08:56 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	pid_t	pid[2];
	int		i;

	if (argc != 5)
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile", 2), exit(1);
	check_args(argv);
	check_open_files(argc, argv, &pipex);
	pipex.num_cmds = argc - 2;
	create_pipes(&pipex);
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

pid_t	first_execution(int index, char *argv[], char *envp[], t_pipex *pipex)
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
		execute_command(argv[index + 2], envp);
	}
	return (pid);
}

pid_t	last_execution(int index, char *argv[], char *envp[], t_pipex *pipex)
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
		execute_command(argv[index + 2], envp);
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
			ft_putstr_fd("Error: empty arg", 2), exit(1);
		i++;
	}
}

void	check_open_files(int argc, char *argv[], t_pipex *pipex)
{
	int	infile;
	int	outfile;

	infile = open(argv[1], O_RDONLY, 644);
	if (infile == -1 || access(argv[1], F_OK | R_OK) == -1)
		my_perr("No such file or directory", false);
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 644);
	if (outfile == -1)
		my_perr("output open check", true);
	pipex->infile = infile;
	pipex->outfile = outfile;
}

void	create_pipes(t_pipex *pipex)
{
	if (pipe(pipex->pd) == -1)
		my_perr("pipe", true);
}
