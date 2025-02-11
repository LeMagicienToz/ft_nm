NAME=		ft_nm

SRCS=		main.c

OBJS=		$(SRCS:.c=.o)

CC=			gcc
CFLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=address 

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf $$'\033[1m*\033[0m'

do:
	@make $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS)
	@echo $$'\n✅ \033[1;32mproject compiled\033[0m ✅'

clean:
	@rm -f $(OBJS)
	@echo $$'\033[1;31mremoved object files\033[0m'

fclean: clean
	@rm -f $(NAME)
	@echo $$'\033[1;31mremoved $(NAME)\033[0m'

re: fclean all
