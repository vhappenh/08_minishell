NAME := #Put name here!!!

CFLAGS := -Wall -Werror -Wextra -g

CC := cc

LIBFT := ./src/libft/

ARCH := ./src/libft/libft.a

OBJ_P := ./obj/

SRC :=

OBJ := $(SRC:%.c=$(OBJ_P)%.o)

$(OBJ_P)%.o:%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@ 

.SILENT:

.PHONY:
	all clean fclean re

all: $(NAME)

vpath %.c src

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT)
	$(CC) -o $(NAME) $(OBJ) $(ARCH)
	echo "The executable: push_swap was created!"

clean:
	rm -f $(OBJ)
	rm -f -d $(OBJ_P)
	$(MAKE) clean -C $(LIBFT)
	echo "The push_swap o_files where removed!"

fclean:	clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT)
	echo "The executable: push_swap was removed!"

re:	fclean all
