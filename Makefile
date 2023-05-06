NAME := minishell

CFLAGS := -Wall -Werror -Wextra -g

CC := cc

LIBFT := ./src/libft_ultra/

ARCH := ./src/libft_ultra/libft.a

OBJ_P := ./obj/

SRC :=	main.c\
		env_parse.c\
		input_parse.c\
		ft_free.c\
		built_ins.c\
		built_in_cd.c\
		built_in_echo.c\
		built_in_env.c\
		built_in_exit.c\
		built_in_export.c\
		built_in_export_utils.c\
		built_in_pwd.c\
		built_in_unset.c\
		utils_shlvl.c\
		utils_lsts.c\
		utils_prompt.c\
		utils_input.c\
		utils_files.c\
		utils_token.c\
		utils_universal.c\
		utils_heredoc.c\
		utils_syntax.c\
		utils_env.c\
		utils_openin.c\
		utils_signals.c\
		pipex_traitor1.c\
		utils_pipex.c

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
