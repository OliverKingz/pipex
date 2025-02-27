/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:42:34 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/27 00:22:27 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_struct(int argc, char *argv[], t_pipex *pipex)
{
	pipex->in_fd = -1;
	pipex->out_fd = -1;
	pipex->pipe_fd[0] = -1;
	pipex->pipe_fd[1] = -1;
	pipex->prev_pipe_fd = -1;
	pipex->here_doc_flag = FALSE;
	pipex->num_cmds = -1;
	pipex->pid = NULL;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipex->here_doc_flag = TRUE;
		pipex->num_cmds = argc - 4;
	}
	if (pipex->here_doc_flag == FALSE)
		pipex->num_cmds = argc - 3;
	pipex->pid = ft_calloc(pipex->num_cmds, sizeof(pid_t));
	if (!pipex->pid)
		my_perr(ERR_MSG_MALLOC, true);
}

void	init_pipes(t_pipex *pipex)
{
	if (pipe(pipex->pipe_fd) == -1)
		(clean(pipex), my_perr("pipe", true));
}
