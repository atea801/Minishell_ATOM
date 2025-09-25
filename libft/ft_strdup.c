/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:52:34 by codespace         #+#    #+#             */
/*   Updated: 2025/05/06 10:41:16 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(char *str)
{
	int		i;
	int		len;
	char	*ptr;

	i = 0;
	len = ft_strlen(str);
	ptr = (char *)malloc((sizeof (char)) * (len + 1));
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
// int main()
// {
// 	char	*src = "gougougagak";
// 	char	*dest = "clarté";
// 	printf("%s\n", ft_strdup(src));
// }
