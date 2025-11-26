/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_2_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:04:29 by tlorette          #+#    #+#             */
/*   Updated: 2025/11/26 11:10:44 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

void	secure_fds_after_open(int *fd_in, int *fd_out)
{
	if (*fd_in != -1 && *fd_in != 0)
		close(*fd_in);
	if (*fd_out != -1 && *fd_out != 1)
		close(*fd_out);
	*fd_in = -1;
	*fd_out = -1;
}
