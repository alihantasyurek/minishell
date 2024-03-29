NAME    := minishell
CC      := cc
INCLUDE := ./includes
CFLAGS  := -I$(INCLUDE) -I./libft
LIBFT   := libft
FLAGS   := -Wall -Wextra -Werror -g
OBJE    := obje/

SRC     :=  build/builtin.c \
            build/cd.c     \
            build/echo.c   \
            build/env.c    \
            build/exit.c   \
            build/export.c \
            build/pwd.c    \
            build/unset.c  \
            check/check.c \
            execve/exec_utils.c \
            execve/exec.c \
            execve/execve.c \
            execve/execve1.c \
            expander/expander.c \
            expander/expander2.c \
            expander/expander_utils.c \
            files/create_files.c \
            files/create_files_utils.c \
            files/dup2_fd.c \
            free/exec_free.c \
            free/exec_free2.c \
            free/free.c \
            heredoc/heredoc.c \
            heredoc/heredoc_utils.c \
            init/init.c \
            lexer/lexer.c \
            main/main.c \
            parser/parser.c \
            parser/parser_utils.c \
            signal/signal.c \
            utils/utils.c \
            utils/utils_2.c \
            utils/env.c

OBJ     := $(addprefix $(OBJE),$(SRC:%.c=%.o))

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(RED)Process still continues...$(NC)"
	@make -C $(LIBFT)
	@cp libft/libft.a .
	@$(CC) $(FLAGS) $(CFLAGS) $(OBJ) libft.a -lreadline -o $(NAME)
	@echo "$(GREEN)Done!$(NC)"

$(OBJE)%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning..."
	@make clean -C $(LIBFT)
	@rm -rf libft.a
	@rm -rf $(OBJE)
	@echo "$(GREEN)Done!$(NC)"

fclean:
	@echo "Cleaning with name..."
	@make fclean -C $(LIBFT)
	@rm -rf libft.a
	@rm -rf $(OBJE)
	@rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
