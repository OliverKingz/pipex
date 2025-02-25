/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:37:59 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/25 18:59:48 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_doc(char *argv[], char *envp[], t_pipex *pipex)
{
	int		i;
	int		status;

	i = -1;
	while (++i < pipex->num_cmds)
	{
		printf("Comando %d\n", i);
		if (i == 0)
			pipex->pid[i] = first_execution(i + 1, argv, envp, pipex);
		else if (i == pipex->num_cmds - 1)
			pipex->pid[i] = last_execution(i + 1, argv, envp, pipex);
		else
			pipex->pid[i] = middle_execution(i + 1, argv, envp, pipex);
	}
	close_fds(pipex);
	i = -1;
	while (++i < pipex->num_cmds)
		waitpid(pipex->pid[i], &status, 0);
	my_free(pipex->pid);
	return (status);
}

int	my_pipex(char *argv[], char *envp[], t_pipex *pipex)
{
	int		i;
	int		status;

	i = -1;
	while (++i < pipex->num_cmds)
	{
		printf("Comando %d\n", i);
		if (i == 0)
			pipex->pid[i] = first_execution(i, argv, envp, pipex);
		else if (i == pipex->num_cmds - 1)
			pipex->pid[i] = last_execution(i, argv, envp, pipex);
		else
			pipex->pid[i] = middle_execution(i, argv, envp, pipex);
	}
	close_fds(pipex);
	i = -1;
	while (++i < pipex->num_cmds)
		waitpid(pipex->pid[i], &status, 0);
	my_free(pipex->pid);
	return (status);
}
