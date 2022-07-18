/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseijo-p <jseijo-p@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 12:43:47 by jseijo-p          #+#    #+#             */
/*   Updated: 2022/07/18 09:58:16 by jseijo-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"

int	ft_isprime(int nb)
{
	int	i;

	if (nb < 2)
		return (0);
	i = 2;
	while (i * i <= nb)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*res;

	i = 0;
	len = (int)ft_strlen(s1) + (int)ft_strlen(s2) + 1;
	res = (char*)malloc(len * sizeof(char));
	if (!res)
		return (NULL);
	while (s1 && s1[i] != '\0')
	{
		res[i] = (char)s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] != '\0')
	{
		res[i + j] = (char)s2[j];
		j++;
	}
	return (res);
}

int gcd(int a, int h)
{
	int temp;
	while(1)
	{
		temp = a % h;
		if(temp == 0)
			return h;
		a = h;
		h = temp;
	}
}
