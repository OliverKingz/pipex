/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:42:34 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/24 21:43:13 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_struct(int argc, char *argv[], t_pipex *pipex)
{
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
	pipex->pipe_fd[0][0] = -1;
	pipex->pipe_fd[0][1] = -1;
	pipex->pipe_fd[1][0] = -1;
	pipex->pipe_fd[1][1] = -1;
	pipex->here_doc = false;
	pipex->num_cmds = -1;
	pipex->pid = NULL;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		pipex->here_doc = true;
	if (!pipex->here_doc)
		pipex->num_cmds = argc - 3;
	else
		pipex->num_cmds = argc - 4;
	pipex->pid = ft_calloc(pipex->num_cmds, sizeof(pid_t));
	if (!pipex->pid)
		my_perr(ERR_MSG_MALLOC, true);
}

void	init_pipes(t_pipex *pipex)
{
	if (pipe(pipex->pipe_fd[0]) == -1)
		(clean(pipex), my_perr("pipe", true));
	if (pipex->num_cmds > 2)
	{
		if (pipe(pipex->pipe_fd[1]) == -1)
			(clean(pipex), my_perr("pipe", true));
	}
}
