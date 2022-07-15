/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 12:43:26 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/07/13 17:26:50 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"

char	*get_next_line(int fd)
{
	char	*s;
	char	*c;

	s = (char *)malloc(10000);
	c = s;
	while (read(fd, c, 1) > 0 && *c != '\n')
		c++;
	if (c > s)
	{
		*c = 0;
		return (s);
	}
	free(s);
	return (0);
}
