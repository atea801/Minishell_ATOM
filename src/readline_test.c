/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:38:50 by aautret           #+#    #+#             */
/*   Updated: 2025/09/22 17:18:50 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../atom.h"

int	main(void)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input || ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
		{
			if (valide_quote(input) == 1)
				printf("Invalide quote\n");
			add_history(input);
		}
		printf("Vous avez tapé : %s\n", input);
		free(input);
	}
	rl_clear_history();
	return (0);
}
