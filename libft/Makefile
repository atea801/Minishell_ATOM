NAME = libft.a

SRC  = ft_isalpha.c \
	ft_isdigit.c \
	ft_atoi.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memset.c \
	ft_strlen.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memrchr.c \
	ft_memset.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_putnbr_fd.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_split.c \
	ft_strcmp.c \
	ft_substr.c \
	ft_calloc.c \

SRCS_BONUS = ft_lstadd_back_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstnew_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lsttiter_bonus.c \
	ft_lstmap_bonus.c \

OBJ  = $(SRC:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c libft.h
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

bonus: $(OBJS) $(OBJS_BONUS)
		$(AR) -rcs $(NAME) $(OBJS) $(OBJS_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
