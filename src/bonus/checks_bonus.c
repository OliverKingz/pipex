/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:55:15 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/27 02:30:42 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_args(int argc, char *argv[])
{
	bool	in_empty;
	bool	out_empty;

	in_empty = false;
	out_empty = false;
	if (ft_strlen(argv[1]) == 0)
		in_empty = true;
	if (ft_strlen(argv[argc - 1]) == 0)
		out_empty = true;
	if (in_empty && out_empty)
	{
		ft_putstr_fd(ERR_MSG_NO_SUCH_FILE, 2);
		(ft_putstr_fd(ERR_MSG_NO_SUCH_FILE, 2), exit(EXIT_FAILURE));
	}
}

char	*check_addpath_cmd(char *command, char *envp[], t_pipex *pipex)
{
	char	*path;
	char	*path_cmd;

	if (!command || ft_strlen(command) == 0)
		return (NULL);
	if (ft_strchr(command, '/') != NULL)
	{
		if (access(command, F_OK | X_OK) == 0)
			return (ft_strdup(command));
		else
		{
			ft_putstr_fd(command, 2);
			ft_putstr_fd(ERR_MSG_CMD_NOT_FOUND, 2);
			return (NULL);
		}
	}
	path = my_getpath(envp);
	path_cmd = my_addpath_cmd(command, path, pipex);
	if (path_cmd == NULL)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(ERR_MSG_CMD_NOT_FOUND, 2);
		return (my_free((void **)&path), NULL);
	}
	return (my_free((void **)&path), path_cmd);
}

char	*my_addpath_cmd(char *command, char *path, t_pipex *pipex)
{
	char	*path_dir;
	char	*path_cmd;

	if (!command || !path)
		return (NULL);
	path_dir = ft_strtok(path, ":");
	path_cmd = NULL;
	while (path_dir != NULL)
	{
		path_cmd = ft_strjoin_char(path_dir, command, '/');
		if (!path_cmd)
			(clean(pipex), my_perr(ERR_MSG_MALLOC, true));
		if (access(path_cmd, F_OK | X_OK) == 0)
			break ;
		else
		{
			my_free((void **)&path_cmd);
			path_dir = ft_strtok(NULL, ":");
		}
	}
	if (path_dir == NULL)
		return (NULL);
	return (path_cmd);
}

char	*my_getpath(char *envp[])
{
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (ft_strdup(path));
}
