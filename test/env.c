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

int	main(int argc, char *argv[], char *envp[])
{
	for (int i = 0; envp[i] != NULL; i++) {
		printf("%s\n", envp[i]);
	}
	return (EXIT_SUCCESS);
}