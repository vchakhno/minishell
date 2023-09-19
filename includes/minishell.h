/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekhaled <ekhaled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:15:05 by ekhaled           #+#    #+#             */
/*   Updated: 2023/09/19 16:17:52 by ekhaled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# define SUCCESS 1
# define FAILURE 0

/*-------- Tokenizer --------*/

enum e_token_type
{
	DLESS_TOKEN,
	DGREAT_TOKEN,
	LESS_TOKEN,
	GREAT_TOKEN,
	WORD_TOKEN,
	NEWLINE_TOKEN,
	IO_NUMBER_TOKEN,
	AND_IF_TOKEN,
	OR_IF_TOKEN,
	PIPE_TOKEN,
	LPAR_TOKEN,
	RPAR_TOKEN
};

typedef struct s_nstr
{
	char		*ptr;
	uint32_t	len;
}	t_nstr;

typedef struct s_token
{
	enum e_token_type	type;
	t_nstr				content;
}	t_token;

/*-------- AST --------*/

enum e_node_type
{
	AND_NODE,
	OR_NODE
};

typedef struct s_and_or_node	t_and_or_node;
typedef struct s_pipe_node		t_pipe_node;
typedef struct s_cmd_prefix		t_cmd_prefix;
typedef struct s_cmd_suffix		t_cmd_suffix;

typedef struct s_io_here
{
	uint32_t			io_number;
	t_token				delimiter;
}	t_io_here;

typedef struct s_io_file
{
	uint32_t			io_number;
	enum e_token_type	redir_type;
	t_token				filename;
}	t_io_file;

typedef struct s_io_redirect
{
	t_io_file		*io_file;
	t_io_here		*io_here;
}	t_io_redirect;

typedef struct s_cmd_suffix
{
	t_cmd_suffix	*cmd_suffix;
	t_io_redirect	*io_redirect;
	t_token			cmd_arg;
}	t_cmd_suffix;

typedef struct s_cmd_prefix
{
	t_cmd_prefix	*cmd_prefix;
	t_io_redirect	*io_redirect;
}	t_cmd_prefix;

typedef struct s_cmd_node
{
	t_token			cmd_name;
	t_cmd_prefix	*cmd_prefix;
	t_cmd_suffix	*cmd_suffix;
}	t_cmd_node;

typedef struct s_pipe_node
{
	t_pipe_node		*left;
	t_cmd_node		*right;
}	t_pipe_node;

typedef struct s_and_or_node
{
	enum e_node_type	type;
	t_and_or_node		*left;
	t_pipe_node			*right;
}	t_and_or_node;

/*-------- Session --------*/

typedef struct s_history
{

}	t_history;

typedef struct s_env
{

}	t_env;

typedef struct s_session
{
	t_history	history;
	t_env		env;
	uint8_t		last_cmd_status;
	bool		is_interactive;
	bool		should_exit;
}	t_session;

#endif