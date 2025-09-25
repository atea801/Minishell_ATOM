/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:55:24 by aautret           #+#    #+#             */
/*   Updated: 2025/09/25 10:36:13 by tlorette         ###   ########.fr       */
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
	char			*type;    // MOT PIPE REDIRIN REDIROUT HERDOC
	struct s_token	*next;
}					t_token;

typedef	struct s_cmd
{
	char	*echo;
	char	*pwd;

}				t_cmd;


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
void	put_token(t_token **token, char *res);
void	tokenizer(t_token *token, char *str);
void	print_token_list(t_token *head);
void	print_token_list_type(t_token *head);
void	copy_word(char *res, char *str, int end, int start);
char	*malloc_token(int end, int start);
//definition des types
char	*type_mot(char *res);
char	*type_pipe(char *res);
char	*type_redir(char *res);
char	*type_heredoc(char *res);
char	*get_token_type(char *res);
int		check_error(char *res);
void	print_error(char *res);



#endif
