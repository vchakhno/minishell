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
				environment/env_var.c \
				grammar/command/builtins/cat.c \
				grammar/command/builtins/cd.c \
				grammar/command/builtins/exit.c \
				grammar/command/builtins/export.c \
				grammar/command/builtins/pwd.c \
				grammar/command/executables/executable.c \
				grammar/command/executables/find_executable.c \
				grammar/command/expand/expand.c \
				grammar/command/redirections/backup_fds.c \
				grammar/command/redirections/cmd_redir.c \
				grammar/command/redirections/heredoc.c \
				grammar/command/argument.c \
				grammar/command/raw_command.c \
				grammar/command/simple_command.c \
				grammar/pipes/pipeline.c \
				grammar/root.c \
				text/input.c \
				text/lines.c \
				tokens/token.c \
				tokens/tokenizer.c \
				utils/fork.c \
				utils/move_fd.c \
				utils/print_error.c \
				main.c \
				session.c
SRCS		:= $(addprefix $(SRC_DIR)/,$(SRCS))

INCS		:=	includes

BUILD_DIR	:= .build
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d)

# **************************************************************************** #
# 	LIBRARIES																   #
# **************************************************************************** #

LIB_DIR		?= $(dir $(abspath $(firstword $(MAKEFILE_LIST))))lib
LIBS		:= ft readline
LIB_TARGETS	:= libft/libft.a
LIB_TARGETS	:= $(addprefix $(LIB_DIR)/,$(LIB_TARGETS))
LIB_INCS	:= libft/include/
INCS		+= $(addprefix $(LIB_DIR)/,$(LIB_INCS))

# **************************************************************************** #
# 	COMPILATION																   #
# **************************************************************************** #

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -g -gdwarf-4
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

$(LIB_DIR):
	@mkdir -p $(LIB_DIR)

$(LIB_DIR)/libft/: | $(LIB_DIR)
	git clone git@github.com:vchakhno/libft.git $(LIB_DIR)/libft

.SECONDEXPANSION:
$(LIB_TARGETS): $(LIB_DIR)/%.a: | $(LIB_DIR)/$$(dir %.a)
	make LIB_DIR=$(LIB_DIR) -C $(dir $@)
