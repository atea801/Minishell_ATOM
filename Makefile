# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlorette <tlorette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/23 17:41:33 by aautret           #+#    #+#              #
#    Updated: 2025/09/26 17:51:54 by tlorette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/parsing_1/parsing_1.c \
		src/parsing_1/add_redir_space.c \
		src/parsing_1/clear_input/clear_input_utils.c \
		src/parsing_1/clear_input/clear_input.c \
		src/tokenization/token.c \
		src/tokenization/quote_gestion.c \
		src/tokenization/token_utils.c \
		src/tokenization/find_type.c \
		src/main.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I. -g
LDFLAGS = -lreadline
LIBFT = ./libft/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) $(OBJ) $(LIBFT) $(LDFLAGS) -o $@

%.o: %.c Atom.h
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
	@valgrind --suppressions=./ignore.supp --leak-check=full --track-origins=yes --trace-children=yes --track-fds=yes -s ./$(NAME)

clean:
	make -C libft clean
	rm -f $(OBJ)
	rm -f ignore.supp

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re ignore val
