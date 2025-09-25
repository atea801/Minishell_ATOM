/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:13:47 by tlorette          #+#    #+#             */
/*   Updated: 2025/05/06 16:23:40 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	size_t			i;
	unsigned int	len_s;
	size_t			malloc_len;

	if (!s)
		return (NULL);
	len_s = ft_strlen((char *)s);
	if (start > len_s)
		return (ft_strdup(""));
	malloc_len = len_s - start;
	if (malloc_len > len)
		malloc_len = len;
	ptr = (char *)malloc((sizeof(char)) * (malloc_len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < malloc_len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
#include <stdio.h>

int	main()
{
	printf("%s\n", ft_substr("coco dingo", 5, 10));
}*/
