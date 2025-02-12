/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 23:30:16 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/11 23:59:02 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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