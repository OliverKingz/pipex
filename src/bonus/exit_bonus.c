/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:47:57 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/27 02:19:12 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	my_perr(const char *msg, bool should_exit)
{
	perror(msg);
	if (should_exit)
		exit(EXIT_FAILURE);
}

void	my_free2d(void **array2d)
{
	int	i;

	i = 0;
	while (array2d[i] != NULL)
	{
		my_free((void **)&array2d[i]);
		i++;
	}
	my_free((void **)&array2d);
}

void	my_free(void **allocatedMemory)
{
	if (*allocatedMemory != NULL)
	{
		free(*allocatedMemory);
		*allocatedMemory = NULL;
	}
}

void	close_fds(t_pipex *pipex)
{
	if (pipex->in_fd != -1)
		close(pipex->in_fd);
	if (pipex->out_fd != -1)
		close(pipex->out_fd);
	if (pipex->pipe_fd[0] != -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pipe_fd[1] != -1)
		close(pipex->pipe_fd[1]);
	if (pipex->prev_pipe_fd != -1)
		close(pipex->prev_pipe_fd);
}

void	clean(t_pipex *pipex)
{
	close_fds(pipex);
	if (pipex->pid)
		my_free((void **)&pipex->pid);
	if (pipex->here_doc_flag == TRUE)
		unlink(HERE_DOC_FILE);
}
