/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 16:55:24 by aautret           #+#    #+#             */
/*   Updated: 2025/11/22 16:01:12 by tlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOM_H
# define ATOM_H

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/****************************************************************************
 *								VARIABLES									*
 ****************************************************************************/

# define BUFFER_SIZE 4096

// typedef enum e_flag
// {
// 	OUT
// 	REDIR_IN
// 	NB_FLAG;
// }	t_flag;

extern volatile sig_atomic_t	g_signal_received;

/****************************************************************************
 *							QUOTE VALIDATION								*
 ****************************************************************************/

/**
 * @brief États possibles pour la state machine de validation des quotes
 *
 * STATE_NORMAL: En dehors de toute quote
 * STATE_SINGLE: À l'intérieur de quotes simples '...'
 * STATE_DOUBLE: À l'intérieur de quotes doubles "..."
 */
typedef enum e_quote_state_simple
{
	STATE_NORMAL = 0,
	STATE_SINGLE = 1,
	STATE_DOUBLE = 2
}								t_quote_state_simple;

/**
 * @brief Contexte de validation des quotes avec informations détaillées
 *
 * Pour diagnostic et debug si nécessaire
 */
typedef struct s_quote_context_simple
{
	t_quote_state_simple		current_state;
	int error_pos;   // -1 si OK, sinon position erreur
	char *error_msg; // Message d'erreur détaillé
	char *input;     // Input analysé (pour debug)
}								t_quote_context_simple;

typedef struct s_token
{
	char						*head;
	char						*value;
	char						*type;
	int quote_type; // 0=normal, 1=single_quote, 2=double_quote
	struct s_token				*next;
}								t_token;

typedef struct s_token_2
{
	char						*head;
	char						*value;
	char						*type;
	int							is_expand;
	struct s_token_2			*next;
}								t_token_2;

typedef struct s_cmd
{
	char						**argv;
	char						*infile;
	char						*outfile;
	char						**heredoc_delim;
	char						*path;
	int							append;
	int							here_doc;
	int							fd_in;
	int							fd_out;
	int							argc;
	int							count_heredocs;
	int							has_redir_error;
	struct s_cmd				*next;
}								t_cmd;

typedef struct s_atom_env
{
	char						*env_head;
	char						*value;
	char						*key;
	bool						has_value;
	bool						has_twin;
	int							size;
	struct s_atom_env			*next;
}								t_atom_env;

typedef struct s_shell_buffers
{
	char						*prompt;
	char						*input;
	char						*res;
	int							**pipes;
	int							num_cmd;
}								t_shell_buffers;

typedef struct s_minishell
{
	t_token						*tok1;
	t_token_2					*tok2;
	t_cmd						*cmd;
	t_atom_env					*env;
	t_shell_buffers				buffers;
	int							exit_code;
	bool						should_execute;
	bool						should_exit;
}								t_minishell;

/****************************************************************************
 ****************************************************************************

*								FUNCTIONS									*

****************************************************************************
****************************************************************************/

/***************************************************************************
 *								EVIRONNEMENT								*
 ****************************************************************************/
// env_list_to_tabs_utils.c
int								count_var_env(t_atom_env *env_list);
void							free_allocated_tab(char **tab, int i);
char							**create_box_tab_env(int count);
void							free_for_env_list_to_tab(char **tab, int i);
int								allocate_content_box_tabs(t_atom_env *env_list,
									char **tab, int count);

// env_list_to_tabs.c
void							fill_up_box_tabs(t_atom_env *env_list,
									char **tab, int count);
char							**env_list_to_tab_new(t_atom_env *env_list);

// env_list_to_tabs.c
char							**env_list_to_tab(t_atom_env *env_list);
char							**env_list_to_tab_new(t_atom_env *env_list);

// env_node.c
void							add_node_to_end(t_atom_env **env_head,
									char *key, char *value);
t_atom_env						*init_new_node_env(char *key, char *value);
void							valide_key(t_atom_env **env_head,
									char *env_line);
int								change_node_list(t_atom_env **env, char *key,
									char *value);
void							delete_node_list(t_atom_env **env, char *key);

// env_path.c
void							create_minimal_env(t_atom_env **env);
char							*get_home(char *cwd);
char							*get_username(char *cwd);

// env_utils.c
char							*get_key(char *env_line);
char							*get_value(char *env_line);
char							*search_in_list(t_atom_env **env, char *key);

// env.c
void							put_key_and_value(t_atom_env **env,
									char *env_line, int islast);
void							my_getenv(t_atom_env **my_env, char **env);

/************************************************************************
 *								PARSING 1								*
 ************************************************************************/
// clear_input_utils.c
int								is_space(char c);
int								count_space(char *str);
int								count_words(char *str);
int								copy_quote(char *str, char *res, int i, int *j);
int								skip_and_flag_space(char *str, int i,
									int *flag);

// clear_input.c
int								skip_space(char *str);
int								calc_res_len_quote(char *str, int i, int *len);
int								calc_res_len(char *str, int i);
char							*epur(char *str, char *res, int i);
char							*clear_input(char *input);

// add_redir_space.c
void							add_space_before_redir(char *input, char *res,
									int i, int *j);
char							*add_redir_space(char *input);
int								count_pipe(char *input);
char							*add_pipe_space(char *input);
char							*add_space_to_operator(char *input);

// parse_1_utils.c
int								is_triple_redir(char *input, int i);
int								is_double_redir(char *input, int i);
int								handle_double_redir(char *input, char *res,
									int *i, int *j);
int								handle_single_redir(char *input, char *res,
									int *i, int *j);
int								is_redir(char c);

// parsing_1.c
// int								valide_quote(char *str);
int								validate_quotes_improved(char *str);
void							free_quote_context_simple(t_quote_context_simple *ctx);
char							*parsing_1(t_minishell *shell, char *input);

/************************************************************************
 *								TOKENIZER 1							*
 ************************************************************************/
// error_type.c
void							set_token_error(t_token **t_head);

// find_type.c
char							*type_mot(char *res);
char							*type_pipe(char *res);
char							*type_redir(char *res);
char							*type_heredoc(char *res);
char							*get_token_type(char *res);

// find_type_2.c
char							*type_expand(char *res);

// quote_gestion.c
int								quote_state(char i, char next);
int								skip_quote(char *str, int i);
void							handle_quote_state(t_token **token, char *str,
									int *start, int end);
int								handle_quote(t_token **token, char *str,
									int *start, int end);

void							handle_general(t_token **token, char *str,
									int *start, int end);
int								handle_all(t_token **token, char *str,
									int start, int i);

// token_utils.c
void							print_token_list(t_token *head);
void							print_token_list_type(t_token *head);
void							copy_word(char *res, char *str, int end,
									int start);
int								put_token(t_token **token, char *res);
int								put_token_with_quote(t_token **token, char *res,
									int quote_type);
void							print_token_2_list(t_token_2 *token_2);
char							*malloc_token(int end, int start);

// tokenizer_1.c
void							tokenizer(t_token *token, char *str);

// check_token.c

void							print_redir_error(t_token **error_token);
int								check_redir_in(t_token *t_head);
int								check_redir_out(t_token *t_head);
int								check_redir_alone(t_token *t_head);
int								check_only_redir(t_token *t_head);

int								malloc_args(t_token **token);

/************************************************************************
 *								PARSING 2								*
 ************************************************************************/
// pars_2_check_valide.c
int								parse_redir_alone(t_token **token_2);
char							*check_pipe(t_token *token_2);
t_token							*check_error(t_token *token_head);
int								check_all(t_minishell *shell,
									t_token **token_head);
int								check_redir(t_token **token_head);

// pars_2_cmd_node_utils.c
void							free_delete_node_list(t_cmd *node);
void							free_init_new_node_cmd(t_cmd *new_node);
int								open_all_redirs_from_tokens(t_token_2 *tokens,
									int *fd_in, int *fd_out);

// pars_2_cmd_node.c
void							add_node_to_end_cmd(t_cmd **cmd_head,
									char **argv);
t_cmd							*init_new_node_cmd(char **argv);
int								add_arg_to_cmd(t_cmd *cmd, char *arg);
void							delete_node_list_cmd(t_cmd **cmd_list);
void							set_cmd_redirection(t_cmd *cmd, char *type,
									char *file);

// pars_2_utils.c
int								count_cmd(t_token *token_head);
int								open_redir_file(char *type, char *file,
									int *old_fd);
int								open_all_redirs_from_tokens(t_token_2 *tokens,
									int *fd_in, int *fd_out);
int								count_args_to_pipe(t_token_2 *token_2);
int								count_cmd(t_token *token_head);
int								open_redir_file(char *type, char *file,
									int *old_fd);
int								open_all_redirs_from_tokens(t_token_2 *tokens,
									int *fd_in, int *fd_out);
int								count_args_to_pipe(t_token_2 *token_2);

// pars_2.c
int								parsing_2(t_minishell *shell,
									t_token *token_head, t_token_2 *token_2);
int								parsing_2(t_minishell *shell,
									t_token *token_head, t_token_2 *token_2);

// token_2_to_cmd.c
int								count_args_to_pipe(t_token_2 *token_2);
void							token_2_to_cmd(t_cmd **cmd,
									t_token_2 **token_2);
void							fill_cmd_until_pipe(t_cmd *cmd,
									t_token_2 **t_head_2);
void							print_cmd_list(t_cmd *cmd);
void							set_heredoc_delim_append(t_token_2 **token_2,
									t_cmd **cmd);
void							set_infile_cmd(t_token_2 **token_2,
									t_cmd **cmd);
int								open_all_redirs_from_tokens(t_token_2 *tokens,
									int *fd_in, int *fd_out);
void							process_current_redirection(t_cmd *cmd,
									t_token_2 *token);

/************************************************************************
 *								TOKENIZER 2								*
 ************************************************************************/
// token_2_find_type.c
void							fill_cmd(t_token **token_1,
									t_token_2 **token_2);
void							fill_args(t_token **token_1,
									t_token_2 **token_2);
void							fill_heredoc_append(t_token **token_1,
									t_token_2 **token_2);
void							fill_redirin_redirout(t_token **token_1,
									t_token_2 **token_2);
void							fill_expand(t_token **token_1,
									t_token_2 **token_2);
void							fill_cmd(t_token **token_1,
									t_token_2 **token_2);
void							fill_args(t_token **token_1,
									t_token_2 **token_2);
void							fill_heredoc_append(t_token **token_1,
									t_token_2 **token_2);
void							fill_redirin_redirout(t_token **token_1,
									t_token_2 **token_2);
void							fill_expand(t_token **token_1,
									t_token_2 **token_2);

// token_2_type.c
void							put_token_2(t_token_2 **token_2);
char							*malloc_cmd(char *str);
char							*copy_token_value(char *str);
int								get_pos(t_token *token_head_1,
									t_token_2 *token_head_2, int first_word);
void							put_token_2(t_token_2 **token_2);
char							*malloc_cmd(char *str);
char							*copy_token_value(char *str);
int								get_pos(t_token *token_head_1,
									t_token_2 *token_head_2, int first_word);

// tokenizer_2.c
void							get_input_pos(t_token **token_1,
									t_token_2 **token_2);
void							set_infile_outfile(t_token_2 **token_2);
void							set_heredoc_delim(t_token_2 **token_2);
void							tokenizer_2(t_token *token_head,
									t_token_2 *token_2);
void							set_cmd_heredoc_delim(t_cmd *cmd, char *file);

/************************************************************************
 *								CHECK_EXPANDABLE						*
 ************************************************************************/
// check_expand.c
void							expand_all_vars(t_minishell *shell,
									t_token_2 *token);
void							expander(t_minishell *shell, char *res, char *s,
									int i);

// expand_utils.c
void							expand_all_tokens(t_minishell *shell,
									t_token_2 *head);
char							*replace_env_var(t_minishell *shell, char *s);
void							check_expendable(char *res, t_token_2 *token_2);
int								in_single_quote(char *res, int pos);
int								in_double_quote(char *res, int pos);
void							expand_all_tokens(t_minishell *shell,
									t_token_2 *head);
char							*replace_env_var(t_minishell *shell, char *s);
void							check_expendable(char *res, t_token_2 *token_2);
int								in_single_quote(char *res, int pos);
int								in_double_quote(char *res, int pos);

/************************************************************************
 *								BUILT_IN								*
 ************************************************************************/
// built-in_dispatcher.c
int								execute_builtin(t_minishell *shell);
int								execute_builtin(t_minishell *shell);

// built_in.c
int								is_builtin(char *cmd);
int								is_builtin(char *cmd);

// echo.c
int								check_echo_dollar(t_minishell *shell);
int								restore_dollar_in_argv(t_minishell *shell);
int								builtin_echo(t_minishell *shell);
int								echo_completed(t_minishell *shell);
int								check_echo_dollar(t_minishell *shell);
int								restore_dollar_in_argv(t_minishell *shell);
int								builtin_echo(t_minishell *shell);
int								echo_completed(t_minishell *shell);

// echo_utils.c
int								echo_parser(t_cmd *cmd);
int								search_dollar_in_list(t_token *tok1);
int								echo_parser(t_cmd *cmd);
int								search_dollar_in_list(t_token *tok1);
void							print_echo_args(t_cmd *cmd, int out_fd,
									int start);

// export.c
int								builtin_export(t_minishell *shell);

// pwd.c
int								builtin_pwd(t_minishell *shell);
int								pwd_parser(t_minishell *shell);
int								builtin_pwd(t_minishell *shell);
int								pwd_parser(t_minishell *shell);

// env.c
int								builtin_env(t_minishell *shell);
int								builtin_env(t_minishell *shell);

// exit.c
int								builtin_exit(t_minishell *shell);
int								builtin_exit(t_minishell *shell);

// cd.c
int								cd_init_vars(t_minishell *shell, char **home,
									char **oldpwd);
int								cd_dispatch_case(t_minishell *shell, char *home,
									char *oldpwd, char *new_pwd);
int								builtin_cd(t_minishell *shell);
int								cd_init_vars(t_minishell *shell, char **home,
									char **oldpwd);
int								cd_dispatch_case(t_minishell *shell, char *home,
									char *oldpwd, char *new_pwd);
int								builtin_cd(t_minishell *shell);

// cd_utils.c
void							cd_update_env(t_minishell *shell, char *old_pwd,
									char *new_pwd);
void							cd_with_args_free(char *old_pwd, char *path);
void							cd_with_args_error_print(char *path);
void							cd_update_env(t_minishell *shell, char *old_pwd,
									char *new_pwd);
void							cd_with_args_free(char *old_pwd, char *path);
void							cd_with_args_error_print(char *path);

// cd_case.c
int								case_cd_sin_arg(t_minishell *shell, char *home,
									char *old_pwd, char *new_pwd);
int								cd_special_case_dash(t_minishell *shell,
									char *old_pwd, char *new_pwd);
int								cd_with_args(t_minishell *shell, char *old_pwd,
									char *new_pwd);
int								case_cd_sin_arg(t_minishell *shell, char *home,
									char *old_pwd, char *new_pwd);
int								cd_special_case_dash(t_minishell *shell,
									char *old_pwd, char *new_pwd);
int								cd_with_args(t_minishell *shell, char *old_pwd,
									char *new_pwd);

// unset.c
int								builtin_unset(t_minishell *shell);

/************************************************************************
 *								EXEC									*
 ************************************************************************/
// exec_single_cmd.c
void							redirect_input(char *file);
void							redirect_output(char *file);
void							redirect_append(char *file);
void							handle_redirections(t_cmd *cmd);
void							exec_single_cmd(t_minishell *shell);
void							redirect_input(char *file);
void							redirect_output(char *file);
void							redirect_append(char *file);
void							handle_redirections(t_cmd *cmd);

// exec_single_utils.c
int								check_fork_error(t_minishell *shell,
									t_cmd *cmd);
void							secure_exec(t_cmd *cmd, char **tab_to_env);
int								unfound_path(t_cmd *cmd, t_minishell *shell);
int								init_cmd_path(t_cmd *cmd, t_minishell *shell);
void							close_fds(t_cmd *cmd);
int								check_fork_error(t_minishell *shell,
									t_cmd *cmd);
void							secure_exec(t_cmd *cmd, char **tab_to_env);
int								unfound_path(t_cmd *cmd, t_minishell *shell);
int								init_cmd_path(t_cmd *cmd, t_minishell *shell);
void							close_fds(t_cmd *cmd);

// exec_multipipe.c
void							wait_all_childrens(pid_t *pids, int num_cmds,
									t_minishell *shell);
void							execute_multipipe(t_minishell *shell,
									t_cmd *cmd);
void							wait_all_childrens(pid_t *pids, int num_cmds,
									t_minishell *shell);
void							close_all_buffer_pipes(t_minishell *shell,
									pid_t *pids, int num_cmd, int i);
void							inside_child_security(t_minishell *shell,
									t_cmd *current, int num_cmd, int i);

// multipipe_utils.c
int								count_commands(t_cmd *cmd_list);
int								**create_pipes(int num_pipes);
void							free_pipes(int **pipes, int num_pipes);
void							close_all_pipes(int **pipes, int num_pipes);
void							setup_pipe_redirections(int **pipes,
									int cmd_index, int num_cmds, t_cmd *cmd);
int								count_commands(t_cmd *cmd_list);
int								**create_pipes(int num_pipes);
void							free_pipes(int **pipes, int num_pipes);
void							close_all_pipes(int **pipes, int num_pipes);
void							setup_pipe_redirections(int **pipes,
									int cmd_index, int num_cmds, t_cmd *cmd);

// multipipe_utils_2.c
void							last_heredoc_checker(t_cmd *cmd, int *p_fd,
									int index);
int								check_pid_error(int **pipes, int num_cmd);
void							close_all_cmd_fds(t_cmd *cmd_list);
int								cleanup_on_error(pid_t *pids, int num_cmd,
									t_minishell *shell);
void							multi_heredoc_readline(char *line,
									char *delimiter, int *p_fd,
									t_minishell *shell);
void							handle_child_status(t_minishell *shell,
									int status);
// multipipe_utils_3.c
void							write_ctrld_error_msg(t_minishell *shell,
									char *delimiter, int *p_fd);
void							free_and_close_before_ctrlc(t_minishell *shell,
									char *line, int *p_fd);
void							free_and_close_before_delim(t_minishell *shell,
									char *line, int *p_fd);
void							path_not_found_exe_child(t_minishell *shell,
									t_cmd *cmd, int num_cmd, char **env);
void							clean_built_in_checker(t_minishell *shell,
									char **env, int num_cmd);

// exec_heredoc.c
int								heredoc_detected(t_token_2 *token2);
int								exec_heredoc(t_cmd *cmd, int *pipe_fd,
									t_atom_env *env, t_minishell *shell);
void							here_doc_infile(t_cmd *cmd, t_atom_env *env,
									t_minishell *shell);
void							write_here_doc(char *line, int *pipe_fd,
									t_atom_env *env);
int								process_heredocs(t_cmd *cmd,
									t_minishell *shell);
void							secure_fd_in_after_heredoc(t_cmd *cmd,
									int index);

// exec_multiple_heredoc.c
void							free_heredoc_delims(char **delims);
char							**extract_heredoc_delims(t_cmd *cmd);
int								count_and_extract_heredocs(t_cmd *cmd);
int								multiple_heredoc_gestion(t_cmd *cmd,
									t_minishell *shell, int index);
int								exec_multiple_heredoc(t_cmd *cmd,
									t_minishell *shell);

// exec_signals_utils.c
void							handle_multi_heredoc_child(int *p_fd,
									char *delimiter, t_minishell *shell);
char							*heredoc_readline(int **pipe_fd, t_cmd *cmd);
void							heredoc_signal_test(int *p_fd, pid_t pid,
									int *status);
int								multi_heredoc_signal_test(pid_t pid, int *p_fd);
void							exec_single_cmd_child(t_minishell *shell);

/************************************************************************
 *								SIGNALS									*
 ************************************************************************/
// signals.c
void							handle_sigint_prompt(int sig);
void							setup_signals_prompt(void);
void							restore_default_signals(void);
void							handle_signals_heredoc(int sig);
void							setup_signals_heredoc(void);
void							handle_sigint_heredoc_parent(int sig);
void							setup_signals_heredoc_parent(void);

/************************************************************************
 *								MYPRINTLIST								*
 ************************************************************************/
// my_print_list_1.c
void							print_env_list(t_atom_env *env_head);
void							print_env_tab(char **tab_env);
void							print_cmd_list(t_cmd *cmd);
void							print_token_2_list(t_token_2 *token_2);
void							print_token_2_list_type(t_token_2 *token_2);

// my_print_list_2.c
void							print_token_list(t_token *head);
void							print_token_list_type(t_token *head);

// exec_utils.c
char							*find_command_path(char *cmd,
									t_minishell *shell);
char							**get_path(t_atom_env *env);
void							free_tab(char **tab);

// exec_utils_2.c
int								count_commands(t_cmd *cmd_list);
int								**create_pipes(int num_pipes);
void							free_pipes(int **pipes, int num_pipes);
void							close_all_pipes(int **pipes, int num_pipes);
void							setup_pipe_redirections(int **pipes,
									int cmd_index, int num_cmds, t_cmd *cmd);
// exec_multipipe.c
void							execute_multipipe(t_minishell *shell,
									t_cmd *cmd);

/************************************************************************
 *								SRC										*
 ************************************************************************/
// init.c
int								init_token_struct(t_token **token_head,
									t_token_2 **token_2);
int								init_env_struct(t_atom_env **env_head);
int								init_cmd_struct(t_cmd **cmd_list);
void							init_all(t_atom_env **env_head,
									t_token **token_head, char **env,
									t_token_2 **token_2);

// src_utils.c
void							free_all(t_token *token_head,
									t_atom_env *env_head, t_token_2 *token_2);
void							free_token_list(t_token *head,
									t_token_2 *head_2);
void							free_env_list(t_atom_env *head);
void							free_cmd_list(t_cmd *cmd_list);
void							free_env_tab(char **tab_env);
void							free_all_life(t_minishell *shell);

// src_utils_2.c
void							free_token_1_only(t_token *head);
void							free_token_2_list(t_token_2 **head_2);

// init.c
int								init_token_1_only(t_token **token_head);

// main.c
char							*get_dynamic_prompt(void);
void							res_to_tokenizer1(t_minishell *shell);
void							my_readline(int ac, char **argv,
									t_minishell *shell);

#endif
