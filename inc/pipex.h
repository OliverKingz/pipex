/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:54:25 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/19 16:39:48 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/wait.h> // To use wait, waitpid,
/*
Libraries already included at libft.
#include <stdio.h>  // To use printf, perror, strerror,
#include <stdlib.h> // To use malloc, free, exit. Also size_t def.
// To use write, open, read, close, fork, execve, pipe, dup, dup2, access, unlink
#include <unistd.h> 
*/
typedef struct s_pipex
{
	int	infile;
	int	outfile;
	int	pd[2];
	int	num_cmds;
}		t_pipex;

int		main(int argc, char *argv[], char *envp[]);
void	execute_command(char *command, char *envp[]);
char	*check_addpath_cmd(char *command, char *envp[]);
char	*my_getpath(char *envp[]);
char	*my_addpath_cmd(char *command, char *path);

pid_t	first_execution(int index, char *argv[], char *envp[], t_pipex *pipex);
pid_t	last_execution(int index, char *argv[], char *envp[], t_pipex *pipex);

void	check_args(char *argv[]);
void	check_open_files(int argc, char *argv[], t_pipex *pipex);
void	create_pipes(t_pipex *pipex);

void	my_perr(const char *msg, bool should_exit);
void	my_free2d(void **array2d);
void	my_free(void *allocatedMemory);
void	init_struct(t_pipex *pipex);

/*
Input Command	Description	Expected Output
./pipex infile "ls -l" "wc -l" outfile	Lists files in infile directory and counts lines.	Number of lines from ls -l written to outfile.
./pipex infile "grep a1" "wc -w" outfile	Searches for lines containing "a1" in infile and counts words.	Number of words in lines containing "a1" written to outfile.
./pipex infile "cat" "wc -c" outfile	Outputs the content of infile and counts characters.	Number of characters in infile written to outfile.
./pipex infile "echo Hello" "tr 'a-z' 'A-Z'" outfile	Echoes "Hello" and converts it to uppercase.	HELLO written to outfile.
./pipex infile "sort" "uniq" outfile	Sorts the content of infile and removes duplicate lines.	Sorted and deduplicated content written to outfile.
./pipex infile "cut -d: -f1" "sort" outfile	Extracts the first field from infile (colon-separated) and sorts it.	Sorted list of first fields written to outfile.
./pipex infile "awk '{print $1}'" "wc -l" outfile	Extracts the first column from infile and counts lines.	Number of lines in the first column written to outfile.
./pipex infile "sed 's/foo/bar/'" "wc -c" outfile	Replaces "foo" with "bar" in infile and counts characters.	Number of characters after replacement written to outfile.
./pipex infile "head -n 5" "tail -n 1" outfile	Extracts the first 5 lines of infile and then the last line of those 5.	The 5th line of infile written to outfile.
./pipex infile "tr ' ' '\n'" "sort" outfile	Splits words in infile by spaces and sorts them.	Sorted list of words written to outfile.
*/