NAME := minishell

CFLAGS := -Wall -Werror -Wextra -g

CC := cc

LIBFT := ./src/libft_ultra/

ARCH := ./src/libft_ultra/libft.a

OBJ_P := ./obj/

SRC :=	main.c\
		input_parse.c\
		execute.c\
		ft_free.c\
		utils1.c\
		utils_prompt.c\
		utils_input.c\
		utils_files.c\
		utils_token.c

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
	$(MAKE) -C $(LIBFT)
	$(CC) -lreadline -o $(NAME) $(OBJ) $(ARCH)
	echo "The executable: minishell was created!"

clean:
	rm -f $(OBJ)
	rm -f -rd $(OBJ_P)
	$(MAKE) clean -C $(LIBFT)
	echo "The minishell o_files where removed!"

fclean:	clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT)
	echo "The executable: minishell was removed!"

re:	fclean all

norm:
	norminette -R CheckForbiddenSourceHeader src/*.c src/vr.h
