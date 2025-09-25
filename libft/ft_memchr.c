/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 08:13:51 by codespace         #+#    #+#             */
/*   Updated: 2025/05/01 11:33:49 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
	{
		if (ptr[i] == (char)c)
			return ((void *)(ptr + i));
		i++;
	}
	return (NULL);
}
// int	main()
// {
// 	printf("%s\n", (char *)ft_memchr("pamoison", 'm', 20));
// }