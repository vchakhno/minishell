# **************************************************************************** #
# 	Makefile based on clemedon's Makefile tutorial							   #
# **************************************************************************** #

NAME		:= minishell

# **************************************************************************** #
# 	SOURCES																	   #
# **************************************************************************** #

SRC_DIR		:= sources
SRCS		:= \
				environment/env.c \
				environment/env_vars.c \
				environment/env_var.c \
				grammar/and_or/and_or.c \
				grammar/and_or/run_and_or.c \
				grammar/command/builtins/cd.c \
				grammar/command/builtins/echo.c \
				grammar/command/builtins/env.c \
				grammar/command/builtins/exit.c \
				grammar/command/builtins/export.c \
				grammar/command/builtins/pwd.c \
				grammar/command/builtins/unset.c \
				grammar/command/builtins/utils.c \
				grammar/command/executables/compact.c \
				grammar/command/executables/executable.c \
				grammar/command/executables/find_executable.c \
				grammar/command/expand/args.c \
				grammar/command/expand/fields.c \
				grammar/command/expand/quotes.c \
				grammar/command/expand/redir.c \
				grammar/command/expand/utils.c \
				grammar/command/expand/var.c \
				grammar/command/redirections/append.c \
				grammar/command/redirections/backup_fds.c \
				grammar/command/redirections/heredoc.c \
				grammar/command/redirections/run_heredoc.c \
				grammar/command/redirections/input.c \
				grammar/command/redirections/output.c \
				grammar/command/redirections/redirection.c \
				grammar/command/redirections/redirections.c \
				grammar/command/argument.c \
				grammar/command/raw_command.c \
				grammar/command/simple_command.c \
				grammar/pipes/pipeline_elem.c \
				grammar/pipes/pipeline.c \
				grammar/pipes/pipes.c \
				grammar/pipes/run_pipeline.c \
				grammar/newlines.c \
				grammar/root.c \
				shell_input/input.c \
				shell_input/lines.c \
				shell_input/shell_input.c \
				tokens/alloc.c \
				tokens/ops.c \
				tokens/token_manip.c \
				tokens/token.c \
				tokens/tokenizer.c \
				utils/fork.c \
				utils/move_fd.c \
				utils/print_error.c \
				utils/clear_stdout.c \
				main.c \
				runtime_context.c \
				session.c
SRCS		:= $(addprefix $(SRC_DIR)/,$(SRCS))

INCS		:=	includes

BUILD_DIR	:= .build
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

# **************************************************************************** #
# 	LIBRARIES																   #
# **************************************************************************** #

LIB_DIR		:= lib
LIBS		:= ft readline
LIB_TARGETS	:= libft/libft.a
LIB_TARGETS	:= $(addprefix $(LIB_DIR)/,$(LIB_TARGETS))
LIB_INCS	:= libft/include/
INCS		+= $(addprefix $(LIB_DIR)/,$(LIB_INCS))

# **************************************************************************** #
# 	COMPILATION																   #
# **************************************************************************** #

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror #-g -gdwarf-4
CPPFLAGS	:= $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS		:= $(addprefix -L,$(dir $(LIB_TARGETS)))
LDLIBS		:= $(addprefix -l,$(LIBS))
AR			:= ar -rcs

# **************************************************************************** #
# 	UTILITIES																   #
# **************************************************************************** #

RM			:= rm -rf
MAKEFLAGS   += --no-print-directory
DIR_DUP		= @mkdir -p $(@D)

# **************************************************************************** #
# 	RECIPIES :D																   #
# **************************************************************************** #

all: $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(LIB_TARGETS) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)

-include $(DEPS)

clean:
	make fclean -C $(LIB_DIR)/libft
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
# 	DEPENDENCIES :3															   #
# **************************************************************************** #

.SECONDEXPANSION:
$(LIB_TARGETS): $(LIB_DIR)/%.a: | $(LIB_DIR)/$$(dir %.a)
	make LIB_DIR=$(LIB_DIR) -C $(dir $@)
