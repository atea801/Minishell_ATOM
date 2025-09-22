/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:36:02 by codespace         #+#    #+#             */
/*   Updated: 2025/05/01 11:33:10 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrchr(const void *s, int c, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n--)
	{
		if (ptr[n] == (char)c)
			return ((void *)(ptr + n));
	}
	return (NULL);
}
// int	main()
// {
// 	printf("%s\n", (char*)ft_memrchr("Caillou", 'a', 10));
// }