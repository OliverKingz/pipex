/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:35:09 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/21 23:09:41 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	pid_t	pid[2];
	int		i;
	int		status;

	if (argc != 5)
		(ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2), exit(1));
	check_args(argc, argv);
	init_struct(argc, &pipex);
	check_open_files(argc, argv, &pipex);
	init_pipes(&pipex);
	i = 0;
	while (i < pipex.num_cmds)
	{
		if (i == 0)
			pid[i] = first_execution(i, argv, envp, &pipex);
		if (i == pipex.num_cmds - 1)
			pid[i] = last_execution(i, argv, envp, &pipex);
		i++;
	}
	close_fds(&pipex);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	return (WEXITSTATUS(status));
}
// while (waitpid(-1, NULL, 0) > 0);