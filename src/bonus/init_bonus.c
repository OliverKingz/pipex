/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:42:34 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/27 02:26:40 by ozamora-         ###   ########.fr       */
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

void	init_files(int argc, char *argv[], t_pipex *pipex)
{
	pipex->in_fd = open(argv[1], O_RDONLY);
	if (pipex->in_fd == -1)
	{
		my_perr(argv[1], false);
		pipex->in_fd = open("/dev/null", O_RDONLY);
		if (pipex->in_fd == -1)
			(clean(pipex), my_perr("/dev/null", true));
	}
	pipex->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->out_fd == -1)
		(my_perr(argv[argc - 1], false));
}

void	init_files_heredoc(int argc, char *argv[], t_pipex *pipex)
{
	pipex->in_fd = open(HERE_DOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->in_fd == -1)
		(clean(pipex), my_perr(HERE_DOC_FILE, false));
	write_here_doc(argv[2], pipex);
	close(pipex->in_fd);
	pipex->in_fd = open(HERE_DOC_FILE, O_RDONLY);
	if (pipex->in_fd == -1)
		(clean(pipex), my_perr(HERE_DOC_FILE, false));
	pipex->out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipex->out_fd == -1)
		(my_perr(argv[argc - 1], false));
}

void	init_pipes(t_pipex *pipex)
{
	if (pipe(pipex->pipe_fd) == -1)
		(clean(pipex), my_perr("pipe", true));
}
