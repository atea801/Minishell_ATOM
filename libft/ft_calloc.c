/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:35:21 by tlorette          #+#    #+#             */
/*   Updated: 2025/05/02 16:00:56 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc((size) * (nmemb));
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (size * nmemb));
	return (ptr);
}
