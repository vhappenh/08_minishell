NAME := minishell

CFLAGS := -Wall -Werror -Wextra -g

CC := cc

LIBFT := ./src/libft_ultra/

ARCH := ./src/libft_ultra/libft.a

OBJ_P := ./obj/

SRC :=	main.c\
		built_in_cd.c\
		built_in_echo.c\
		built_in_env.c\
		built_in_exit.c\
		built_in_export_utils.c\
		built_in_export.c\
		built_in_pwd.c\
		built_in_unset.c\
		built_ins.c\
		env_parse.c\
		free_utils.c\
		free.c\
		input_check_for_env.c\
		input_check_open_pipe.c\
		input_files.c\
		input_heredoc_utils.c\
		input_heredoc.c\
		input_parse.c\
		input_prompt.c\
		input_token.c\
		pipex.c\
		signals.c\
		syntax_check.c\
		utils_check_for_env.c\
		utils_input.c\
		utils_lsts.c\
		utils_pipex.c\
		utils_shlvl.c\
		utils_universal.c

OBJ := $(SRC:%.c=$(OBJ_P)%.o)

$(OBJ_P)%.o:%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@ 

.SILENT:

.PHONY:
	all clean fclean re norm

all: $(NAME)

vpath %.c src

$(NAME): $(OBJ)
	echo "compiling..."
	$(MAKE) -s -C $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(ARCH) -lreadline
	echo "The executable: minishell was created!"

clean:
	rm -f $(OBJ)
	rm -f -rd $(OBJ_P)
	$(MAKE) -s clean -C $(LIBFT)
	echo "The minishell o_files where removed!"

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -s fclean -C $(LIBFT)
	echo "The executable: minishell was removed!"

re:	fclean all

norm:
	norminette -R CheckForbiddenSourceHeader src/*.c src/vr.h

val: all
	valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=./minishell.supp ./minishell
