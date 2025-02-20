/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:54:25 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/20 16:23:13 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* ************************************************************************** */
# include "libft.h"
# include <sys/wait.h> // To use wait, waitpid,
/* Libraries already included at libft.
# include <stdio.h> // To use printf, perror, strerror,
# include <stdlib.h>// To use malloc, free, exit. Also size_t def.
# include <unistd.h>// To use write, open, read, close, fork, execve, pipe
					// dup, dup2, access, unlink*/

/* ************************************************************************** */
typedef struct s_pipex
{
	int	infile;
	int	outfile;
	int	pd[2];
	int	num_cmds;
}		t_pipex;

/* ************************************************************************** */

int		main(int argc, char *argv[], char *envp[]);

void	init_struct(int argc, t_pipex *pipex);
void	init_pipes(t_pipex *pipex);

void	execute_command(char *command, char *envp[], t_pipex *pipex);
pid_t	first_execution(int i, char *argv[], char *envp[], t_pipex *pipex);
pid_t	last_execution(int i, char *argv[], char *envp[], t_pipex *pipex);

void	check_args(int argc, char *argv[]);
void	check_open_files(int argc, char *argv[], t_pipex *pipex);
char	*check_addpath_cmd(char *command, char *envp[], t_pipex *pipex);
char	*my_getpath(char *envp[]);
char	*my_addpath_cmd(char *command, char *path, t_pipex *pipex);

void	my_perr(const char *msg, bool should_exit);
void	my_free2d(void **array2d);
void	my_free(void *allocatedMemory);
void	close_fds(t_pipex *pipex);

/*
Input Command	Description	Expected Output
./pipex infile "ls -l" "wc -l" outfile
./pipex infile "grep a1" "wc -w" outfile
./pipex infile "cat" "wc -c" outfile
./pipex infile "echo Hello" "tr 'a-z' 'A-Z'" outfile
./pipex infile "sort" "uniq" outfile
./pipex infile "cut -d: -f1" "sort" outfile
./pipex infile "awk '{print $1}'" "wc -l" outfile
./pipex infile "sed 's/foo/bar/'" "wc -c" outfile
./pipex infile "head -n 5" "tail -n 1" outfile
./pipex infile "tr ' ' '\n'" "sort" outfile
*/

#endif