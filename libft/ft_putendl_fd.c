/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 10:04:50 by vmazurok          #+#    #+#             */
/*   Updated: 2017/11/07 10:04:51 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putendl_fd(char const *s, int fd)
{
	int i;

	i = -1;
	if (s)
	{
		while (s[++i])
			write(fd, &s[i], 1);
		write(fd, "\n", 1);
	}
}