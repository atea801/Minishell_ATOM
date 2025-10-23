/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:03:44 by codespace         #+#    #+#             */
/*   Updated: 2025/10/23 15:03:43 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	// Si s = "" (chaîne vide)
	while (*s) // *s = '\0' donc on n'entre pas dans la boucle
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')          // Si on cherche '\0'
		return ((char *)s); // On retourne un pointeur vers '\0'
	return (NULL);
}
// int	main(void)
// {
// 	printf("%s\n", ft_strchr("pamoi", 'c'));
// 	return (0);
// }