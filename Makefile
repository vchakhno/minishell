# **************************************************************************** #
# 	Makefile based on clemedon's Makefile tutorial							   #
# **************************************************************************** #

NAME		:= minishell

# **************************************************************************** #
# 	SOURCES																	   #
# **************************************************************************** #

SRC_DIR		:= sources
SRCS		:= \
				main.c \
				session.c \
				token.c \
				lines.c \
				env.c \
				env_var.c \
				tokenizer.c \
				utils/move_fd.c \
				utils/fork.c \
				utils/print_error.c \
				raw_command.c \
				executable.c \
				backup_fds.c \
				find_executable.c \
				ast/root.c \
				ast/simple_command.c \
				ast/pipeline.c \
				ast/cmd_redir.c \
				ast/cmd_arg.c \
				builtins/exit.c \
				builtins/export.c \
				builtins/cd.c \
				builtins/pwd.c \
				builtins/cat.c
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
