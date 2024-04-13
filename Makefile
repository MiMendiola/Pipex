NAME = pipex

# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
CLEAR	=	\033[0m

CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address
CC = cc
RM = rm -f

LIBFTA = libft/libft.a

SRCS = $(addprefix ./src/, pipex.c)

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@make all -sC ./libft
	@echo "$(GREEN)Compiling Libft.$(CLEAR)"
	@$(CC) $(CFLAGS) $(OBJS) -I ../../includes/pipex.h $(LIBFTA) -o $(NAME)
	@echo "$(GREEN)Pipex Compiled.$(CLEAR)"

clean:
	@$(RM) $(OBJS)
	@make clean -sC libft
	@echo "$(RED)All Objs Deleted.$(CLEAR)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFTA)
	@echo "$(RED)Everything Deleted.$(CLEAR)"

re: fclean all

.PHONY: all clean fclean re