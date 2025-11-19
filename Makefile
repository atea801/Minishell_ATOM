# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/23 17:41:33 by aautret           #+#    #+#              #
#    Updated: 2025/11/19 11:04:22 by tlorette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

SRC = src/parsing_1/parsing_1.c \
		src/parsing_1/clear_input/clear_input_utils.c \
		src/parsing_1/clear_input/clear_input.c \
		src/parsing_1/add_redir_space.c \
		src/parsing_1/parse_1_utils.c \
		src/parsing_2/tokenizer_2/token_2_find_type.c \
		src/parsing_2/tokenizer_2/token_2_type.c \
		src/parsing_2/tokenizer_2/tokenizer_2.c \
		src/parsing_2/pars_2_check_valide.c \
		src/parsing_2/pars_2_cmd_node_utils.c \
		src/parsing_2/pars_2_cmd_node.c \
		src/parsing_2/pars_2_utils.c \
		src/parsing_2/pars_2.c \
		src/parsing_2/token_2_to_cmd.c \
		src/tokenizer_1/check_token.c \
		src/tokenizer_1/error_type.c \
		src/tokenizer_1/find_type.c \
		src/tokenizer_1/find_type_2.c \
		src/tokenizer_1/quote_gestion.c \
		src/tokenizer_1/token_utils.c \
		src/tokenizer_1/tokenizer_1.c \
		src/env/env_list_to_tabs_utils.c \
		src/env/env_list_to_tabs.c \
		src/env/env_path.c \
		src/env/env_node.c \
		src/env/env_utils.c \
		src/env/env.c \
		src/myprintlist/my_print_list.c \
		src/myprintlist/my_print_list_2.c \
		src/env/check_expandable/check_expand.c \
		src/env/check_expandable/expand_utils.c \
		src/built_in/built_in_dispatcher.c \
		src/built_in/built_in.c \
		src/built_in/echo.c \
		src/built_in/echo_utils.c \
		src/built_in/pwd.c \
		src/built_in/env.c \
		src/built_in/exit.c \
		src/built_in/cd.c \
		src/built_in/cd_utils.c \
		src/built_in/cd_case.c \
		src/built_in/unset.c \
		src/built_in/export.c \
		src/exec/exec_utils.c \
		src/exec/exec_single_cmd.c \
		src/exec/exec_single_utils.c \
		src/exec/exec_multipipe.c \
		src/exec/multipipe_utils.c \
		src/exec/multipipe_utils_2.c \
		src/exec/exec_heredoc.c \
		src/exec/exec_multiple_heredoc.c \
		src/exec/redirections.c \
		src/exec/signal_utils.c \
		src/init.c\
		src/signals/setup_signals.c\
		src/signals/signal_handler.c\
		src/src_utils.c \
		src/src_utils_2.c \
		src/main.c \

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g -I.
LDFLAGS = -lreadline
LIBFT = ./libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $@

%.o: %.c atom.h
	cc $(CFLAGS) -c $< -o $@

# Règles pour Valgrind avec suppression des leaks readline
ignore:
	@echo "Création du fichier de suppression Valgrind..."
	@echo "{" > ignore.supp
	@echo "   ignore_readline_leaks" >> ignore.supp
	@echo "   Memcheck:Leak" >> ignore.supp
	@echo "   ..." >> ignore.supp
	@echo "   obj:*/libreadline.so.*" >> ignore.supp
	@echo "}" >> ignore.supp
	@echo "{" >> ignore.supp
	@echo "   ignore_bin_functions" >> ignore.supp
	@echo "   Memcheck:Leak" >> ignore.supp
	@echo "   ..." >> ignore.supp
	@echo "   obj:/usr/bin/*" >> ignore.supp
	@echo "}" >> ignore.supp
	@echo "{" >> ignore.supp
	@echo "   ncurses_termcap" >> ignore.supp
	@echo "   Memcheck:Leak" >> ignore.supp
	@echo "   match-leak-kinds:reachable" >> ignore.supp
	@echo "   fun:rl_make_bare_keymap" >> ignore.supp
	@echo "   fun:rl_generic_bind" >> ignore.supp
	@echo "   fun:rl_parse_and_bind" >> ignore.supp
	@echo "   obj:/usr/lib/x86_64-linux-gnu/libreadline.so.8.2" >> ignore.supp
	@echo "   fun:rl_initialize" >> ignore.supp
	@echo "   fun:readline" >> ignore.supp
	@echo "}" >> ignore.supp

val: $(NAME)
	@if ! [ -f "ignore.supp" ]; then make ignore; fi
	@valgrind --suppressions=./ignore.supp --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes --track-fds=yes -s ./$(NAME)

clean:
	make -C libft clean
	rm -f $(OBJ)
	rm -f ignore.supp

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re ignore val
