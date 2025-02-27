/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:38:38 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/27 00:34:35 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* ************************************************************************** */

# include "libft.h"
# include <sys/wait.h> // To use wait, waitpid,

/* Libraries already included at libft.

# include <stdio.h> // To use printf, perror, strerror,
# include <stdlib.h>// To use malloc, free, exit. Also size_t def.
# include <unistd.h>// To use write, open, read, close, fork, execve, pipe
					// dup, dup2, access, unlink */

/* ************************************************************************** */
typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	int		pipe_fd[2];
	int		prev_pipe_fd;
	int		num_cmds;
	pid_t	*pid;
	int		here_doc_flag;
}			t_pipex;

/* ************************************************************************** */
# define TRUE 1
# define FALSE 0

# define STDIN_FILENO 0
# define STDOUT_FILENO 1

# define HERE_DOC_FILE ".here_doc_tmp"

# define ERR_MSG_SYNTAX "syntax error\n"
# define ERR_MSG_CMD_NOT_FOUND ": command not found\n"
# define ERR_MSG_NO_SUCH_FILE "No such file or directory\n"
# define ERR_MSG_MALLOC "malloc"

# define ERR_CMD_NOT_FOUND 127

/* ************************************************************************** */

int			main(int argc, char *argv[], char *envp[]);
int			my_pipex(char *argv[], char *envp[], t_pipex *pipex);
void		write_here_doc(char *limiter, t_pipex *pipex);

void		init_struct(int argc, char *argv[], t_pipex *pipex);
void		init_pipes(t_pipex *pipex);

void		execute_command(char *command, char *envp[], t_pipex *pipex);
pid_t		first_execution(int i, char *argv[], char *envp[], t_pipex *pipex);
pid_t		last_execution(int i, char *argv[], char *envp[], t_pipex *pipex);
pid_t		middle_execution(int i, char *argv[], char *envp[], t_pipex *pipex);

void		check_args(int argc, char *argv[]);
void		check_open_files(int argc, char *argv[], t_pipex *pipex);
char		*check_addpath_cmd(char *command, char *envp[], t_pipex *pipex);
char		*my_getpath(char *envp[]);
char		*my_addpath_cmd(char *command, char *path, t_pipex *pipex);

void		my_perr(const char *msg, bool should_exit);
void		my_free2d(void **array2d);
void		my_free(void **allocatedMemory);
void		close_fds(t_pipex *pipex);
void		clean(t_pipex *pipex);

#endif