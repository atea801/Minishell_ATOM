/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:55:24 by aautret           #+#    #+#             */
/*   Updated: 2025/09/23 16:55:06 by aautret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOM_H
# define ATOM_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// #include <string.h>
// #include <fcntl.h>
// #include <limits>

typedef struct s_token
{
	char			*head;
	char			*value; // le texte du token
	int				type;    // 0 = mot, 1 = opérateur, etc.
	struct s_token	*next;
}					t_token;


//PARSING 1
int		is_space(char c);
int		count_words(char *str);
int		count_space(char *str);
int		skip_space(char *str);
char	*epur(char *str, char *res, int i);
int		valide_quote(char *str);
char	*clear_input(char *input);
char	*parsing_1(char *input);


//TOKENISATION
int		token_type1(char *res);
void	put_token(t_token **token, char *res);
void	tokenizer(t_token *token, char *str);
void	print_token_list(t_token *head);
void	copy_word(char *res, char *str, int end, int start);
char	*malloc_token(int end, int start);

#endif
