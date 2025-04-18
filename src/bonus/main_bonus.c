/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 02:49:53 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/27 02:30:15 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;
	int		status;

	if (argc < 5)
		(ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2), exit(1));
	if (argc < 6 && (ft_strncmp(argv[1], "here_doc", 8) == 0))
	{
		ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1 cmd2 outfile\n", 2);
		exit(1);
	}
	check_args(argc, argv);
	init_struct(argc, argv, &pipex);
	init_pipes(&pipex);
	if (pipex.here_doc_flag == FALSE)
		init_files(argc, argv, &pipex);
	else
		init_files_heredoc(argc, argv, &pipex);
	status = my_pipex(argv, envp, &pipex);
	return (WEXITSTATUS(status));
}
