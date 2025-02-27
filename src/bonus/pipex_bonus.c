/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:37:59 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/27 00:45:04 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	write_here_doc(char *limiter, t_pipex *pipex)
{
	char	*hd_line;
	int		limit_len;

	hd_line = NULL;
	limit_len = ft_strlen(limiter);
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		hd_line = get_next_line(STDIN_FILENO);
		if (!hd_line)
			clean(pipex), my_perr(ERR_MSG_MALLOC, true);
		if (ft_strncmp(hd_line, limiter, limit_len) == 0 
			&& hd_line[ft_strlen(limiter)] == '\n')
			break ;
		(ft_putstr_fd(hd_line, pipex->in_fd), my_free((void**)&hd_line));
	}
	my_free((void**)&hd_line);
}

int	my_pipex(char *argv[], char *envp[], t_pipex *pipex)
{
	int	i;
	int	status;

	i = -1;
	while (++i < pipex->num_cmds)
	{
		//printf("Comando %d: %s\n", i, argv[i + 2 + pipex->here_doc_flag]);
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
	return (clean(pipex), status);
}
