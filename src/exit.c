/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:02:41 by ozamora-          #+#    #+#             */
/*   Updated: 2025/02/14 21:38:15 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	my_perr(const char *msg, bool should_exit)
{
	perror(msg);
	if (should_exit)
		exit(EXIT_FAILURE);
}
