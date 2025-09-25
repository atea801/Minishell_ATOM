/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 12:28:02 by codespace         #+#    #+#             */
/*   Updated: 2025/05/02 12:28:35 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dest_len;

	i = 0;
	dest_len = 0;
	while (dest_len < size && dest[dest_len])
		dest_len++;
	src_len = ft_strlen((char *)src);
	if (dest_len == size)
		return (src_len + size);
	while ((i + dest_len + 1) < size && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[i + dest_len] = '\0';
	return (dest_len + src_len);
}
/*#include <stdio.h>

int main()
{
	char dest[30] = "boiqa";
	int	len = ft_strlcat(dest, "caillou", 10);
	printf("%d\n", len);
}*/