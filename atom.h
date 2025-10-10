/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautret <aautret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:55:24 by aautret           #+#    #+#             */
/*   Updated: 2025/10/10 19:35:27 by aautret          ###   ########.fr       */
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
// >

// typedef enum e_flag
// {
// 	OUT
// 	REDIR_IN
// 	NB_FLAG;
// }	t_flag;

typedef struct s_token
{
	char				*head;
	char *value; // le texte du token
	char *type;  // MOT PIPE REDIRIN REDIROUT HERDOC
	struct s_token		*next;
}						t_token;

typedef struct s_token_2
{
	char				*head;
	char *value; // le texte du token
	char *type;  // CMD ARG INFILE OUTFILE HERE_DOC APPEND
	int					is_expand;
	struct s_token_2	*next;
}						t_token_2;

typedef struct s_cmd
{
	// char				*cmd_head;
	char				*cmd;
	char				**args;
	char				*infile;
	char				*outfile;
	char				*append;
	char				*here_doc;
	int					ac;

	struct s_cmd		*next;
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
 ****************************************************************************

*								FUNCTIONS									*

****************************************************************************
****************************************************************************/

/***************************************************************************
 *								EVIRONNEMENT								*
 ****************************************************************************/
// env_list_to_tabs_utils.c
void					print_env_tab(char **tab_env);
int						count_var_env(t_atom_env *env_list);
char					**create_box_tab_env(int count);
void					free_for_env_list_to_tab(char **tab, int i);
void					allocate_content_box_tabs(t_atom_env *env_list,
							char **tab, int count);

// env_list_to_tabs.c
void					fill_up_box_tabs(t_atom_env *env_list, char **tab,
							int count);
char					**env_list_to_tab(t_atom_env *env_list);

// env_node.c
void					add_node_to_end(t_atom_env **env_head, char *key,
							char *value);
t_atom_env				*init_new_node_env(char *key, char *value);
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
int						copy_quote(char *str, char *res, int i, int *j);
int						skip_and_flag_space(char *str, int i, int *flag);

// clear_input.c
int						skip_space(char *str);
int						calc_res_len_quote(char *str, int i, int *len);
int						calc_res_len(char *str, int i);
char					*epur(char *str, char *res, int i);
char					*clear_input(char *input);

// add_redir_space.c
void					add_space_before_redir(char *input, char *res, int i,
							int *j);
char					*add_redir_space(char *input);
int						count_pipe(char *input);
char					*add_pipe_space(char *input);
char					*add_space_to_operator(char *input);

// parse_1_utils.c
int						is_triple_redir(char *input, int i);
int						is_double_redir(char *input, int i);
int						handle_double_redir(char *input, char *res, int *i,
							int *j);
int						handle_single_redir(char *input, char *res, int *i,
							int *j);
int						is_redir(char c);

// parsing_1.c
int						valide_quote(char *str);
char					*parsing_1(char *input);

/************************************************************************
 *								TOKENIZER 1							*
 ************************************************************************/
// error_type.c
void					set_token_error(t_token **t_head);

// find_type.c
char					*type_mot(char *res);
char					*type_pipe(char *res);
char					*type_redir(char *res);
char					*type_heredoc(char *res);
char					*get_token_type(char *res);

// quote_gestion.c
int						quote_state(char i, char next);
int						skip_quote(char *str, int i);
void					handle_quote_state(t_token **token, char *str,
							int *start, int end);
void					handle_quote(t_token **token, char *str, int *start,
							int end);
void					handle_general(t_token **token, char *str, int *start,
							int end);
void					handle_all(t_token **token, char *str, int start,
							int i);

// token_utils.c
void					print_token_list(t_token *head);
void					print_token_list_type(t_token *head);
void					copy_word(char *res, char *str, int end, int start);
void					put_token(t_token **token, char *res);
char					*malloc_token(int end, int start);

// tokenizer_1.c
void					tokenizer(t_token *token, char *str);

// check_token.c

void					print_redir_error(t_token **t_head);
int						check_redir_in(t_token *t_head);
int						check_redir_out(t_token *t_head);
int						check_redir_alone(t_token *t_head);
int						check_only_redir(t_token *t_head);

int						malloc_args(t_token **token);

/************************************************************************
 *								PARSING 2								*
 ************************************************************************/
// pars_2_check_valide.c
int						parse_redir_alone(t_token **token_2);
int						check_pipe(t_token *token_2);
int						check_error(t_token *token_head);
int						check_all(t_token **token_head);

// pars_2_cmd_node_utils.c
void					free_delete_node_list(t_cmd *node);
void					free_init_new_node_cmd(t_cmd *new_node);

// pars_2_cmd_node.c
void					add_node_to_end_cmd(t_cmd **cmd_head, char *cmd,
							char *args);
t_cmd					*init_new_node_cmd(char *cmd, char *args);
int						change_node_list_cmd(t_cmd **cmd_list, char *cmd,
							char *args);
void					delete_node_list_cmd(t_cmd **cmd_list, char *cmd);

// pars_2_utils.c
int						count_cmd(t_token *token_head);
void					print_token_2_list(t_token_2 *token_2);
void					print_token_2_list_type(t_token_2 *token_2);
// void					print_cmd_list(t_cmd *cmd_list);

// pars_2.c
int						parsing_2(t_token *token_head, t_token_2 *token_2);

/************************************************************************
 *								TOKENIZER 2								*
 ************************************************************************/
// token_2_find_type.c
void					fill_cmd(t_token **token_1, t_token_2 **token_2);
void					fill_args(t_token **token_1, t_token_2 **token_2);
void					fill_heredoc_append(t_token **token_1,
							t_token_2 **token_2);
void					fill_redirin_redirout(t_token **token_1,
							t_token_2 **token_2);

// token_2_type.c
void					put_token_2(t_token_2 **token_2);
char					*malloc_cmd(char *str);
char					*copy_token_value(char *str);
int						get_pos(t_token *token_head_1, t_token_2 *token_head_2,
							int first_word);

// tokenizer_2.c
void					get_input_pos(t_token **token_1, t_token_2 **token_2);
void					set_infile_outfile(t_token_2 **token_2);
void					tokenizer_2(t_token *token_head, t_token_2 *token_2);

/************************************************************************
 *								CHECK_EXPANDABLE						*
 ************************************************************************/
// check_expand.c
int						in_single_quote(char *res, int pos);
int						in_double_quote(char *res, int pos);
void					check_expendable(char *res, t_token_2 *token_2);

/************************************************************************
 *								SRC										*
 ************************************************************************/
// init.c
int						init_token_struct(t_token **token_head,
							t_token_2 **token_2);
int						init_env_struct(t_atom_env **env_head);
int						init_cmd_struct(t_cmd **cmd_list);
void					init_all(t_atom_env **env_head, t_token **token_head,
							char **env, t_token_2 **token_2);

// src_utils.c
void					free_all(t_token *token_head, t_atom_env *env_head,
							t_token_2 *token_2);

void					free_token_list(t_token *head, t_token_2 *head_2);
void					free_env_list(t_atom_env *head);
void					free_cmd_list(t_cmd *cmd_list);
void					free_env_tab(char **tab_env);

// main.c

void					res_to_tokenizer1(t_token **t_head,
							t_token_2 **t_head_2, char *res);
void					my_readline(t_token **t_head, t_token_2 **t_head_2);

#endif
