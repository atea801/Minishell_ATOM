/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:32:24 by tlorette          #+#    #+#             */
/*   Updated: 2025/05/06 16:52:58 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_len(int c)
{
	int	len;
	int	i;

	len = 0;
	i = c;
	if (i < 0)
	len++;
	while (i >= 10 || i <= -10)
	{
		len++;
		i = i / 10;
	}
	len++;
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	n_long;

	len = ft_len(n);
	str = ((char *)malloc(sizeof (char) * (len + 1)));
	if (!str)
		return (NULL);
	n_long = n;
	if (n_long < 0)
	{
		n_long *= -1;
		str[0] = '-';
	}
	str[len] = '\0';
	len--;
	while (n_long >= 10)
	{
		str[len] = n_long % 10 + '0';
		n_long /= 10;
		len--;
	}
	str[len] = n_long % 10 + '0';
	return (str);
}
/*
#include <stdio.h>
int	main(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		printf("result : %s\n", ft_itoa(ft_atoi(av[i])));
		i++;
	}
}*/
