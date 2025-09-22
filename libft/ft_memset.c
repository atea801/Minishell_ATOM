/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:46:24 by tlorette          #+#    #+#             */
/*   Updated: 2025/05/01 10:39:20 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (n > 0)
	{
		str[i] = (char)c;
		i++;
		n--;
	}
	return (s);
}
/*
#include <stdio.h>

int	main()
{
	char	s[20];

	ft_memset(s,'0', 5);
	printf("%s\n", s);
	return (0);
}*/
