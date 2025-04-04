NAME=		ft_nm

SRCS=		src/main.c \
			src/nm64.c \
			src/nm32.c \
			src/utils.c

OBJS=		$(SRCS:.c=.o)

CC=			gcc
CFLAGS	=	-Wall -Wextra -Werror -g

LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf $$'\033[1m*\033[0m'

do:
	@make $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) -o $(NAME) $(OBJS) $(LIBFT) $(CFLAGS)
	@echo $$'\n✅ \033[1;32mproject compiled\033[0m ✅'

$(LIBFT):
	@make -C $(LIBFT_DIR)

fclean:
	@rm -f $(OBJS)
	@rm -f $(NAME)
	@echo $$'\033[1;31mremoved object files\033[0m'
	@make -C $(LIBFT_DIR) fclean

clean:
	@rm -f $(NAME)
	@echo $$'\033[1;31mremoved $(NAME)\033[0m'

re: fclean all
