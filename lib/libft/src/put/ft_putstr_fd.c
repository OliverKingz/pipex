/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:12:12 by ozamora-          #+#    #+#             */
/*   Updated: 2024/11/24 21:06:25 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Sends a string to the specified file descriptor.
 * @param s:  The string to send.
 * @param fd: The file descriptor on which to write.
 * @return Nothing.
 */
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (fd < 0 || s == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
