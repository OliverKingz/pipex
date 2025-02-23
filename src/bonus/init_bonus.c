/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:42:34 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/23 02:47:41 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_struct(int argc, t_pipex *pipex)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->pd[0][0] = -1;
	pipex->pd[0][1] = -1;
	pipex->pd[1][0] = -1;
	pipex->pd[1][1] = -1;
	if (pipex->here_doc == false)
		pipex->num_cmds = argc - 3;
	else
		pipex->num_cmds = argc - 4;
}

void	init_pipes(t_pipex *pipex)
{
	if (pipe(pipex->pd[0]) == -1)
		(close_fds(pipex), my_perr("pipe", true));
	if (pipe(pipex->pd[1]) == -1)
		(close_fds(pipex), my_perr("pipe", true));
}
