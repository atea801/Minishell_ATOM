/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:55:24 by aautret           #+#    #+#             */
/*   Updated: 2025/09/25 17:48:20 by aautret          ###   ########.fr       */
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
# include <stdbool.h>
// #include <string.h>
// #include <fcntl.h>
// #include <limits>


/******************************************************************************
*								VARIABLES									  *
******************************************************************************/
# define REDIR_IN	1	//"<"
// # define HEREDOC	2	//"< <"
# define REDIR_OUT	3	//">"
// # define APPEND		4	//">>"
# define PIPE		5	//"|"
# define WORD		6	//"mot"
// # define CMD		6	//"|"
// # define ARG		7	//"|"

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



/******************************************************************************
*								FUNCTIONS									  *
******************************************************************************/
//PARSING 1

char	*add_redir_space(char *input);
int		count_redir(char *input);

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
int		quote_state(char *str);

//definition des types
char	*type_mot(char *res);
char	*type_pipe(char *res);
char	*type_redir(char *res);
char	*type_heredoc(char *res);
char	*get_token_type(char *res);
int		check_error(char *res);
void	print_error(char *res);



#endif
