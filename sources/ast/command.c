/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/18 15:49:37 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>

bool	alloc_command_ast(t_command_ast *ast)
{
	if (!ft_vector_alloc(&ast->argv, sizeof(t_string), 10))
		return (false);
	if (!ft_vector_alloc(&ast->redirs, sizeof(t_redirection), 10))
	{
		ft_vector_free(ast->argv);
		return (false);
	}
	return (true);
}

bool	parse_command_arg(
	t_command_ast *ast, t_tokenizer *tokenizer, enum e_syntax_error *error
) {
	t_token		token;
	t_string	arg;

	if (!peek_token(tokenizer, &token, "cmd> ", (enum e_prompt_error *)error))
		return (false);
	if (token.type != TOKEN_WORD)
	{
		*error = SYNTAX_ERROR_NO_MATCH;
		return (false);
	}
	consume_token(tokenizer, NULL, NULL);
	if (!ft_string_from_str(&arg, token.content))
	{
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	if (!ft_vector_push(&ast->argv, &arg))
	{
		ft_string_free(arg);
		*error = SYNTAX_ERROR_MALLOC;
		return (false);
	}
	return (true);
}

bool	parse_command_ast(
	t_command_ast *ast, t_tokenizer *tokenizer, enum e_syntax_error *error
) {
	while (true)
	{
		if (parse_command_arg(ast, tokenizer, error))
			continue ;
		if (*error != SYNTAX_ERROR_NO_MATCH)
			return (false);
		if (parse_command_redir(ast, tokenizer, error))
			continue ;
		if (*error != SYNTAX_ERROR_NO_MATCH)
			return (false);
		break ;
	}
	return (ast->argv.size);
}

bool	alloc_exec_argv(t_vector *exec_argv, t_vector args)
{
	t_u32	i;

	if (!ft_vector_alloc(exec_argv, sizeof(char *), args.size + 1))
		return (false);
	i = 0;
	while (i < args.size)
	{
		ft_vector_push(exec_argv, &((t_string *)args.elems)[i].c_str);
		i++;
	}
	ft_vector_push(exec_argv, &(char *){NULL});
	return (true);
}

bool	execute_command_ast(t_command_ast ast, t_session *session)
{
	t_string	full_path;
	t_vector	exec_argv;
	pid_t		pid;
	
	(void) session;
	if (!search_path(&session->env,
			((t_string *)ast.argv.elems)[0].str, &full_path))
		return (false);
	if (!alloc_exec_argv(&exec_argv, ast.argv))
	{
		ft_string_free(full_path);
		return (false);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_string_free(full_path);
		ft_vector_free(exec_argv);
		return (false);
	}
	if (pid == 0)
	{
		execve(
			full_path.c_str,
			(char **)exec_argv.elems,
			(char *[]){NULL});
		exit(0);
	}
	waitpid(pid, NULL, 0);
	ft_vector_free(exec_argv);
	ft_string_free(full_path);
	return (true);
}

void	free_command_ast(t_command_ast ast)
{
	t_u32	i;

	i = 0;
	while (i < ast.argv.size)
	{
		ft_string_free(((t_string *)ast.argv.elems)[i]);
		i++;
	}
	ft_vector_free(ast.argv);
	i = 0;
	while (i < ast.redirs.size)
	{
		ft_string_free(
			((t_redirection *)ast.redirs.elems)[i].filename);
		i++;
	}
	ft_vector_free(ast.redirs);
}
