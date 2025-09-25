/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:13:20 by tlorette          #+#    #+#             */
/*   Updated: 2025/05/01 10:39:13 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*p_dest;
	char	*p_src;

	p_dest = (char *)dest;
	p_src = (char *)src;
	if (!dest && !src)
		return (NULL);
	while (n--)
	{
		*p_dest = *p_src;
		p_dest++;
		p_src++;
	}
	return (dest);
}

/*#include <stdio.h>

int	main(void)
{
	char c[0];
	
	memcpy(c, 0, 0);
	printf("%s\n", c);
	return (0);
}*/
