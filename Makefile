# Variables
NAME = ft_nm

SRCS = src/main.c \
       src/nm64.c \
       src/nm32.c \
       src/utils.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Règles principales
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	@echo $$'\n✅ \033[1;32mproject compiled\033[0m ✅'

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf $$'\033[1m*\033[0m'

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

# Nettoyage
clean:
	@rm -f $(OBJS)
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@echo $$'\033[1;31mremoved object files\033[0m'

fclean: clean
	@rm -f $(NAME)
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@echo $$'\033[1;31mremoved $(NAME)\033[0m'

re: fclean all

# Phonies
.PHONY: all clean fclean re
