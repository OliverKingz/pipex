/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:54:25 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/18 17:26:09 by ozamora-         ###   ########.fr       */
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
	int	fd[2];
}		t_pipex;

//void	execute_command(char *cmd, int input_fd, int output_fd, char *envp[]);
void	execute_command(int index, char *argv[], char *envp[], t_pipex *pipex);
char	*check_addpath_cmd(char *command, char *envp[]);
char	*my_getpath(char *envp[]);

void	check_args(int argc, char *argv[]);
void	check_open_files(int argc, char *argv[], t_pipex *pipex);
void	create_pipes(t_pipex *pipex);

void	my_perr(const char *msg, bool should_exit);
void	my_free2d(void **array2d);

/*
1. File Handling
- open(): Opens a file and returns a file descriptor.
- close(): Closes a file descriptor, freeing up resources.
- unlink(): Deletes a file from the filesystem, used to clean temporary files.

2. Process Management
- fork(): Creates a new process by duplicating the calling process.
Used to execute commands in child processes.
- execve(): Replaces the current process image with a new one.
Used to execute shell commands.
- wait(): Waits for a child process to terminate.
Useful for synchronizing parent and child processes.
- waitpid(): Waits for a specific child process to terminate.
Provides more control than wait().

3. Pipes
- pipe(): Creates a pipe, which is a unidirectional data channel for
inter-process communication. Used to connect commands in a pipeline.
- dup(): Duplicates a file descriptor. Useful for redirecting input/output.
- dup2(): Duplicates a file descriptor and assigns it to a specified fd number.
Used to redirect input/output to/from pipes.

4. Memory Management
- malloc(): Allocates memory on the heap. Used for dynamic memory allocation.
- free(): Deallocates memory previously allocated by malloc(). Prevents memleaks.

5. Error Handling
- perror(): Prints an error message to stderr based on the current value of errno
Useful for debugging.
- strerror(): Returns a string describing the error code stored in errno.
Useful for generating custom error messages.

6. Input/Output
- read(): Reads data from a file descriptor into a buffer.
Used to read input from files or pipes.
- write(): Writes data from a buffer to a file descriptor.
Used to write output to files or pipes.

7. Program Control
- exit(): Terminates the program with a specified status code.
Used to handle errors or normal termination.
- access(): Checks if a file exists or if the program has permission to access it
Useful for error handling.
 */
