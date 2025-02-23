/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:47:57 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/23 23:12:28 by ozamora-         ###   ########.fr       */
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
		my_free(array2d[i]);
		i++;
	}
	my_free(array2d);
}

void	my_free(void *allocatedMemory)
{
	if (allocatedMemory != NULL)
	{
		free(allocatedMemory);
		allocatedMemory = NULL;
	}
}

void	close_fds(t_pipex *pipex)
{
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	if (pipex->pd[0][0] != -1)
		close(pipex->pd[0][0]);
	if (pipex->pd[0][1] != -1)
		close(pipex->pd[0][1]);
	if (pipex->pd[1][0] != -1)
		close(pipex->pd[1][0]);
	if (pipex->pd[1][1] != -1)
		close(pipex->pd[1][1]);

}
