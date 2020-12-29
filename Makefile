NAME		=	minishell

SRC_DIR		=	./src/
SRC			=	init_data.c\
				parser.c\
				get_next_line.c\
				exit.c\
				error.c\
				parser_utils.c\
				split_line.c\
				get_tokens.c\
				str_mask.c\
				validate_tokens.c\
				check_syntax_error.c\
				find_env.c\
				find_env_unset.c\
				correct_tokens.c\
				free_data.c\
				exec_fill.c\
				process_redirect.c\
				find_name.c\
				handle_signals.c\
				b_cd.c\
				b_echo.c\
				b_env.c\
				b_export.c\
				b_pwd.c\
				b_unset.c\
				b_exit.c\
				p_execute.c\
				reallocs.c\
				processor.c\
				preprocess.c\
				env_utils.c\
				path_utils.c\
				builtin_utils.c\
				remake_lenv.c\
				pipe_exec.c\
				redirect_exec.c\
				main.c

O_DIR		=	./bin
OBJ			=	$(addprefix $(O_DIR)/, $(SRC:c=o))

H_DIR		=	./include
INCLUDES	=	$(H_DIR)/*

LIB			=	./libft/libft.a \

FLAGS		= -g# -Wall -Wextra -Werror

all : $(NAME)

$(NAME)	:	$(OBJ) lib
	@clang $(FLAGS) -o $(NAME) $(OBJ) -I $(H_DIR) $(LIB)

lib:
	@make bonus -C ./libft/

$(O_DIR)/%.o: ./src/*/%.c $(INCLUDES) | $(O_DIR)
	@clang $(FLAGS) -I $(H_DIR) -c $< -o $@

$(O_DIR):
	@mkdir $(O_DIR)

clean:
	@rm -rf $(OBJ)
	@rmdir $(O_DIR)
	@echo "$(NAME) object files deleted"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C ./libft/
	@echo "$(NAME) deleted"

re: fclean all

.PHONY: all clean fclean re
