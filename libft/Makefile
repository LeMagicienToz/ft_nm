SRCS =	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_printf.c \
		ft_checkflags.c \
		ft_argputchar.c \
		ft_argputstr.c \
		ft_putchar.c \
		ft_strcmp.c \
		ft_argputchar.c\
		ft_argputstr.c\
		ft_putstr.c\
		ft_argputnbr.c\
		ft_argputnbr_base.c \
		ft_putstr.c \
		ft_argputnbr.c \
		ft_argputnbr_base.c 

SRCB =	ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstsize.c

OBJS	= ${SRCS:.c=.o}
OBJSB	= ${SRCB:.c=.o}

NAME	= libft.a

CC		= gcc
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
	@printf $$'\033[1m*\033[0m'

$(NAME):	${OBJS}
	@ar rc ${NAME} ${OBJS}
	@ranlib ${NAME}
	@echo $$'\n✅ \033[1;32mlibft compiled\033[0m ✅'

all:	${NAME}

clean:
	@${RM} ${OBJS} ${OBJSB}
	@echo $$'\033[1;31mremoved object files\033[0m'

fclean:	clean
	@${RM} ${NAME}
	@echo $$'\033[1;31mremoved ${NAME}\033[0m'

re:	fclean all

bonus: ${OBJS} ${OBJSB}
	@ar rc ${NAME} ${OBJS} ${OBJSB}
	@ranlib ${NAME}
	@echo $$'\n✅ \033[1;32mlibft bonus compiled\033[0m ✅'

.PHONY: all clean fclean re bonus
