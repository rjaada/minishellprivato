NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Colors
GREEN = \033[0;92m
BLUE = \033[0;94m
CYAN = \033[0;96m
YELLOW = \033[0;93m
RESET = \033[0m

# Directories
SRC_DIR = src/
OBJ_DIR = obj/
INC_DIR = includes/
LIBFT_DIR = libraries/libft/

# Source files
SRC_FILES = main.c \
		lexer/lexer_init.c \
		lexer/lexer_token.c \
		lexer/lexer_word.c \
		lexer/lexer_word_utils.c \
		lexer/lexer_utils.c \
		lexer/lexer_expand.c \
		lexer/lexer_expand_utils.c \
		lexer/tokenizer.c \
		lexer/token_print.c \
		input_validation/input_validation.c \
		input_validation/input_validation_utils.c \
		parser/parser.c \
		parser/utilslist.c \
		parser/utilslist2.c \
		parser/parser_utils.c \
		signals/signals.c \
		utils/utils.c \
		utils/utils_mem.c \
		utils/printbanner.c \
		utils/token_utils.c \
		builtins/ft_echo.c \
		builtins/ft_pwd.c \
		builtins/ft_env.c \
		builtins/ft_exit.c \
		builtins/ft_cd.c \
		builtins/ft_unset.c \
		builtins/ft_export.c \
		builtins/ft_export_utils.c \
		builtins/builtin_utils.c \
		execution/execute_ast.c \
		execution/execute_cmd.c \
		execution/setup_pipes.c \
		execution/env_handle.c\
		execution/get_set_env.c\
		execution/exec_cmd.c\
		execution/exec_utils.c\
		execution/redirection_handling.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# Libraries
LIBFT = $(LIBFT_DIR)libft.a
LIBS = -L$(LIBFT_DIR) -lft -lreadline

# Includes
INC = -I$(INC_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(BLUE)🔨 Building minishell...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✨ Minishell is ready!$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)📚 Building libft...$(RESET)"
	@$(MAKE) bonus -C $(LIBFT_DIR) --silent
	@echo "$(GREEN)✓ Libft ready$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@echo "$(YELLOW)🧹 Cleaning objects...$(RESET)"
	@$(MAKE) clean -C $(LIBFT_DIR) --silent
	@$(RM) -r $(OBJ_DIR)
	@echo "$(GREEN)✓ Objects cleaned$(RESET)"

fclean: clean
	@echo "$(YELLOW)🗑️  Deep cleaning...$(RESET)"
	@$(MAKE) fclean -C $(LIBFT_DIR) --silent
	@$(RM) $(NAME)
	@echo "$(GREEN)✨ All clean!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
