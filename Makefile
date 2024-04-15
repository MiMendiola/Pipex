NAME = pipex
NAME_BONUS = pipex_bonus

# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
CLEAR	=	\033[0m

CFLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address
CC = cc
RM = rm -f

LIBFTA = libft/libft.a

SRCS = $(addprefix ./src/pipex/, pipex.c pipes.c checks.c)
SRCS_BONUS = $(addprefix ./src/bonus/, pipex_bonus.c pipes_bonus.c checks_bonus.c)

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all : $(NAME)

bonus : $(NAME_BONUS)

$(NAME) : $(OBJS)
	@make all -sC ./libft
	@echo "$(GREEN)Compiling Libft.$(CLEAR)"
	@$(CC) $(CFLAGS) $(OBJS) -I ../../includes/pipex.h $(LIBFTA) -o $(NAME)
	@echo "$(GREEN)Pipex Compiled.$(CLEAR)"

$(NAME_BONUS) : $(OBJS_BONUS)
	@make all -sC ./libft
	@echo "$(GREEN)Compiling Libft.$(CLEAR)"
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -I ../../includes/pipex.h $(LIBFTA) -o $(NAME_BONUS)
	@echo "$(GREEN)Pipex Bonus Compiled.$(CLEAR)"

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_BONUS)
	@make clean -sC libft
	@echo "$(RED)All Objs Deleted.$(CLEAR)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@$(RM) $(LIBFTA)
	@echo "$(RED)Everything Deleted.$(CLEAR)"

re: fclean all

.PHONY: all clean fclean re