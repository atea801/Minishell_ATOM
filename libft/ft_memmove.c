/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:16:01 by tlorette          #+#    #+#             */
/*   Updated: 2025/05/02 10:40:00 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*p_dest;
	char	*p_src;

	p_dest = (char *)dest;
	p_src = (char *)src;
	if (!src && !dest)
		return (NULL);
	if (p_dest < p_src)
	{
		while (n--)
		{
			*p_dest++ = *p_src++;
		}
	}
	else
	{
		while (n--)
		{
			*(p_dest + n) = *(p_src + n);
		}
	}
	return (dest);
}
// #include <stdio.h>

// int	main(void)
// {
//  	char	c[50];

// 	ft_memmove(c, "PLUS QUE 3 LIGNE !!!", 6);
// 	printf("%s\n", c);
// 	return (0);
// }
