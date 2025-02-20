/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:26:14 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/20 16:43:17 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_args(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strlen(argv[i]) == 0)
				ft_putstr_fd("Error\n", 2);
				exit
		i++;
	}
	// Los 4 no pueden estar vacios
	// Si infile vacio, error y salir
	// Si comandos vacios, entra y no hace nada. No es un error
	// Si outfile vacio, error y salir. 
}

void	check_open_files(int argc, char *argv[], t_pipex *pipex)
{
	pipex->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->outfile == -1)
		(close_fds(pipex), my_perr(argv[argc - 1], false));
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile == -1 || access(argv[1], F_OK | R_OK) == -1)
	{
		my_perr(argv[1], false);
		pipex->infile = open("/dev/null", O_RDONLY);
		if (pipex->infile == -1)
			(close_fds(pipex), my_perr("/dev/null", true));
	}
}

char	*check_addpath_cmd(char *command, char *envp[], t_pipex *pipex)
{
	char	*path;
	char	*path_cmd;

	path = my_getpath(envp);
	if (!path)
		(close_fds(pipex), my_perr("getpath malloc", true));
	path_cmd = my_addpath_cmd(command, path, pipex);
	if (path_cmd == NULL)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	my_free(path);
	return (path_cmd);
}

char	*my_addpath_cmd(char *command, char *path, t_pipex *pipex)
{
	char	*path_dir;
	char	*path_cmd;

	path_dir = ft_strtok(path, ":");
	path_cmd = NULL;
	while (path_dir != NULL)
	{
		path_cmd = ft_strjoin_char(path_dir, command, '/');
		if (!path_cmd)
			(close_fds(pipex), my_perr("malloc", true));
		if (access(path_cmd, F_OK | X_OK) == 0)
			break ;
		else
		{
			my_free(path_cmd);
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
