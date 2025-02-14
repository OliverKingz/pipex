/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:30:16 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/14 17:37:50 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int		open(const char *__file, int __oflag, ...);
int		close(int __fd);
int		unlink(const char *__name);
pid_t	fork(void);
pid_t	wait(int *__stat_loc);
pid_t	waitpid(pid_t __pid, int *__stat_loc, int __options);
int		pipe(int *__pipedes);
int		dup(int __fd);
int		dup2(int __fd, int __fd2);
void	*malloc(size_t __size);
void	free(void *__ptr);
void	perror(const char *__s);
char	*strerror(int errnum);
ssize_t	read(int __fd, void *__buf, size_t __nbytes);
ssize_t	write(int __fd, const void *__buf, size_t __n);
void	exit(int __status);
int		access(const char *__name, int __type);

int	main(void)
{
	int fd[2];

	// Crear un pipe
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	// Crear un proceso hijo
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(fd[0]); // Cerrar ambos extremos del pipe en caso de error
		close(fd[1]);
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		// Proceso hijo
		close(fd[0]); // Cerrar el extremo de lectura (no se usa en el hijo)

		// Redirigir stdout al pipe
		if (dup2(fd[1], 1) == -1)
		{
			perror("dup2");
			close(fd[1]); // Cerrar el extremo de escritura antes de salir
			exit(EXIT_FAILURE);
		}
		close(fd[1]); // Cerrar el file descriptor original

		// Ejecutar "ls -l"
		execlp("ls", "ls", "-l", NULL);
		perror("execlp");   // Si exec falla
		exit(EXIT_FAILURE); // Terminar el proceso hijo con error
	}
	else
	{
		// Proceso padre
		close(fd[1]); // Cerrar el extremo de escritura (no se usa en el padre)

		// Redirigir stdin al pipe
		if (dup2(fd[0], 0) == -1)
		{
			perror("dup2");
			close(fd[0]); // Cerrar el extremo de lectura antes de salir
			wait(NULL);   // Esperar al hijo para evitar zombies
			exit(EXIT_FAILURE);
		}
		close(fd[0]); // Cerrar el file descriptor original

		// Ejecutar "wc -l"
		execlp("wc", "wc", "-l", NULL);
		perror("execlp");   // Si exec falla
		wait(NULL);         // Esperar al hijo para evitar zombies
		exit(EXIT_FAILURE); // Terminar el proceso padre con error
	}

	return (0); // Nunca se alcanza, pero es buena práctica incluirlo
}