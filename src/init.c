/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:23:47 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/20 15:30:27 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(int argc, t_pipex *pipex)
{
	pipex->infile = -1;
	pipex->outfile = -1;
	pipex->pd[0] = -1;
	pipex->pd[1] = -1;
	pipex->num_cmds = -1;
	init_pipes(pipex);
	pipex->num_cmds = argc - 3;
}

void	init_pipes(t_pipex *pipex)
{
	if (pipe(pipex->pd) == -1)
		(close_fds(pipex), my_perr("pipe", true));
}
