/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dynamic_prompt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 17:34:31 by aautret           #+#    #+#             */
/*   Updated: 2025/11/25 18:54:36 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "atom.h"

/**
 * @brief Génère un prompt par défaut en cas d'erreur getcwd
 *
 * Fonction de secours qui crée un prompt avec le nom "Minishell"
 * lorsque getcwd échoue (par exemple si le répertoire courant a été supprimé).
 *
 * @return char* Pointeur vers le prompt formaté
 */
static char	*get_dynamic_prompt_protect(void)
{
	char	*directory;
	char	*prompt_start;
	char	*prompt_mid;
	char	*prompt;

	directory = "Minishell";
	prompt_start = ft_strjoin("\033[1;92m", directory);
	prompt_mid = ft_strjoin(prompt_start, " > ");
	prompt = ft_strjoin(prompt_mid, "\033[0m");
	free(prompt_start);
	free(prompt_mid);
	return (prompt);
}

/**
 * @brief Génère dynamiquement le prompt du shell
 *
 * Crée un prompt coloré affichant le nom du répertoire courant.
 *
 * Cas particuliers:
 * - Si getcwd échoue: utilise get_dynamic_prompt_protect()
 * - Si le répertoire est "/": affiche "/" 
 * - Sinon: affiche uniquement le nom du dernier répertoire du chemin
 *
 * @return char* Pointeur vers le prompt formaté
 *               NULL en cas d'échec d'allocation mémoire
 */
char	*get_dynamic_prompt(void)
{
	char	*cwd;
	char	*directory;
	char	*prompt_start;
	char	*prompt_mid;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (get_dynamic_prompt_protect());
	directory = ft_strrchr(cwd, '/');
	if (directory && directory[1])
		directory++;
	else if (directory && ft_strcmp(cwd, "/") == 0)
		directory = "/";
	else
		directory = "Minishell";
	prompt_start = ft_strjoin("\033[1;92m", directory);
	prompt_mid = ft_strjoin(prompt_start, " > ");
	prompt = ft_strjoin(prompt_mid, "\033[0m");
	free(cwd);
	free(prompt_start);
	free(prompt_mid);
	return (prompt);
}
