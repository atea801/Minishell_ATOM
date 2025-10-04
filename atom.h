/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:55:24 by aautret           #+#    #+#             */
/*   Updated: 2025/10/04 15:42:41 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOM_H
# define ATOM_H

# include "libft/libft.h"
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// #include <string.h>
// #include <fcntl.h>

/****************************************************************************
*								VARIABLES									*
 ****************************************************************************/
# define REDIR_IN 1 //"<"
// # define HEREDOC	2	//"< <"
# define REDIR_OUT 3 //">"
// # define APPEND		4	//">>"
# define PIPE 5 //"|"
# define WORD 6 //"mot"
// # define CMD		6	//"|"
// # define ARG		7	//"|"

typedef struct s_token
{
	char				*head;
	char *value; // le texte du token
	char *type;  // MOT PIPE REDIRIN REDIROUT HERDOC
	struct s_token		*next;
}						t_token;

typedef struct s_cmd
{
	char				*echo;
	char				*pwd;

}						t_cmd;

typedef struct s_atom_env
{
	char				*env_head;
	char				*value;
	char				*key;
	bool				has_value;
	bool				has_twin;
	int					size;
	struct s_atom_env	*next;
}						t_atom_env;

/****************************************************************************

*								FUNCTIONS									*

****************************************************************************/

/***************************************************************************
 *								EVIRONNEMENT								*
 ****************************************************************************/
// env_node.c
void					add_node_to_end(t_atom_env **env_head, char *key,
							char *value);
t_atom_env				*init_new_node(char *key, char *value);
void					valide_key(t_atom_env **env_head, char *env_line);
int						change_node_list(t_atom_env **env, char *key,
							char *value);
void					delete_node_list(t_atom_env **env, char *key);

// env_path.c
void					create_minimal_env(t_atom_env **env);
char					*get_home(char *cwd);
char					*get_username(char *cwd);

// env_utils.c
void					print_env_list(t_atom_env *env_head);
char					*get_key(char *env_line);
char					*get_value(char *env_line);
char					*search_in_list(t_atom_env **env, char *key);

// env.c
void					put_key_and_value(t_atom_env **env, char *env_line);
void					my_getenv(t_atom_env **my_env, char **env);

/************************************************************************
 *								PARSING 1								*
 ************************************************************************/
// clear_input_utils.c
int						is_space(char c);
int						count_space(char *str);
int						count_words(char *str);
int						skip_space(char *str);
char					*epur(char *str, char *res, int i);

// clear_input.c
char					*clear_input(char *input);

// add_redir_space.c
int						count_redir(char *input);
char					*add_redir_space(char *input);

// parsing_1.c
int						valide_quote(char *str);
char					*parsing_1(char *input);

/************************************************************************
 *								TOKENIZATION							*
 ************************************************************************/
// find_type.c
char					*type_mot(char *res);
char					*type_pipe(char *res);
char					*type_redir(char *res);
char					*get_token_type(char *res);
char					*type_heredoc(char *res);

// quote_gestion.c
int						quote_state(char i, char next);
int						skip_quote(char *str, int i);
void					handle_quote_state(t_token **token, char *str,
							int *start, int end);
void					handle_quote(t_token **token, char *str, int *start,
							int end);
void					handle_general(t_token **token, char *str, int *start,
							int end);
void					handle_quote_general(t_token **token, char *str,
							int *start, int i);
void					handle_all(t_token **token, char *str, int start,
							int i);

// token_utils.c
void					print_token_list(t_token *head);
void					print_token_list_type(t_token *head);
// int						check_error(char *res);
// void					print_error(char *res);

// token.c
void					put_token(t_token **token, char *res);
char					*malloc_token(int end, int start);
void					copy_word(char *res, char *str, int end, int start);
void					tokenizer(t_token *token, char *str);

/************************************************************************
 *								SRC										*
 ************************************************************************/
// init.c
int						init_token_struct(t_token **token_head);
int						init_env_struct(t_atom_env **env_head);
void					init_all(t_atom_env **env_head, t_token **token_head,
							char **env);

// src_utils.c
void					free_all(t_token *token_head, t_atom_env *env_head);
void					free_token_list(t_token *head);
void					free_env_list(t_atom_env *head);

// main.c

#endif
