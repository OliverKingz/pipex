/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:49:53 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/24 21:47:18 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		i;
	int		status;

	if (argc < 5)
		(ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2), exit(1));
	check_args(argc, argv);
	init_struct(argc, argv, &pipex);
	check_open_files(argc, argv, &pipex);
	init_pipes(&pipex);
	i = -1;
	while (++i < pipex.num_cmds)
	{
		printf("Comando %d\n", i);
		if (i == 0)
			pipex.pid[i] = first_execution(i, argv, envp, &pipex);
		else if (i == pipex.num_cmds - 1)
			pipex.pid[i] = last_execution(i, argv, envp, &pipex);
		else
			pipex.pid[i] = middle_execution(i, argv, envp, &pipex);
	}
	close_fds(&pipex);
	i = -1;
	while (++i < pipex.num_cmds)
		waitpid(pipex.pid[i], &status, 0);
	return (my_free(pipex.pid), WEXITSTATUS(status));
}
