NAME		=	minishell

SRC_DIR		=	./src/
SRC			=	parser.c\
				validation.c\
				get_next_line.c\
				exit_parser.c\
				main.c

O_DIR		=	./bin
OBJ			=	$(addprefix $(O_DIR)/, $(SRC:c=o))

H_DIR		=	./include
INCLUDES	=	$(H_DIR)/*

LIB			=	./libft/libft.a \

FLAGS		= -g #-Wall -Wextra -Werror

all : $(NAME)

$(NAME)	:	$(OBJ) $(INCLUDES)
	@make bonus -C ./libft/
	@gcc $(FLAGS) -o $(NAME) $(OBJ) -I $(H_DIR) $(LIB)

$(O_DIR)/%.o: ./src/*/%.c $(INCLUDES) | $(O_DIR)
	@gcc $(FLAGS) -I $(H_DIR) -c $< -o $@

$(O_DIR):
	@mkdir $(O_DIR)

clean:
	@rm -rf $(O_DIR)
	@echo "$(NAME) object files deleted"

fclean: clean
	@rm -rf $(NAME)
#	@make fclean -C ./libft/
	@echo "$(NAME) deleted"

re: fclean all

.PHONY: all clean fclean re
