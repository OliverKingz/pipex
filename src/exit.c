/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:02:41 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/18 17:12:10 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	my_perr(const char *msg, bool should_exit)
{
	perror(msg);
	if (should_exit)
		exit(EXIT_FAILURE);
}

void	my_free2d(void **array2d)
{
	int	i;

	i = 0;
	while (array2d[i] != NULL)
	{
		free(array2d[i]);
		i++;
	}
	free(array2d);
}