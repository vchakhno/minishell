/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 01:51:40 by vchakhno          #+#    #+#             */
/*   Updated: 2023/12/22 16:59:19 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

bool	alloc_pipe_ast(t_pipe_ast *ast)
{
	if (!ft_vector_alloc(&ast->pipes, sizeof(t_cmd_ast), 8))
		return (false);
	return (true);
}

bool	parse_pipe_ast(
	t_pipe_ast *ast, t_tokenizer *tokenizer, enum e_syntax_error *error
) {
	t_cmd_ast	command;

	while (true)
	{
		if (!alloc_cmd_ast(&command))
		{
			*error = SYNTAX_ERROR_MALLOC;
			return (false);
		}
		if (!parse_cmd_ast(&command, tokenizer, error))
		{
			free_cmd_ast(command);
			return (false);
		}
		if (!ft_vector_push(&ast->pipes, &command))
		{
			free_cmd_ast(command);
			*error = SYNTAX_ERROR_MALLOC;
			return (false);
		}
		if (!match_token(tokenizer, "|", "pipe>", error))
			return (*error == SYNTAX_ERROR_NO_MATCH);
	}
	return (true);
}

bool	next_pipe(int *input, int pipe_fds[2], bool first, bool last)
{
	if (first)
		*input = STDIN_FILENO;
	else
	{
		if (pipe_fds[1] != STDOUT_FILENO)
			close(pipe_fds[1]);
		if (*input != STDIN_FILENO)
			close(*input);
		*input = pipe_fds[0];
	}
	if (!last)
		return (pipe(pipe_fds) == 0);
	else
	{
		pipe_fds[1] = STDOUT_FILENO;
		pipe_fds[0] = STDIN_FILENO;
	}
	return (true);
}

bool	apply_pipe(int *input, int pipe_fds[2])
{
	if (pipe_fds[0] != STDIN_FILENO)
		close(pipe_fds[0]);
	return (
		move_fd(*input, STDIN_FILENO)
		& (int) move_fd(pipe_fds[1], STDOUT_FILENO)
	);
}

bool	start_pipeline(
	t_pipe_ast ast, pid_t *pids, t_session *session, enum e_exec_error *error
) {
	t_u32		i;
	int			input;
	int			pipe_fds[2];

	i = 0;
	while (i < ast.pipes.size)
	{
		next_pipe(&input, pipe_fds, i == 0, i == ast.pipes.size - 1);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			apply_pipe(&input, pipe_fds);
			if (!execute_cmd_ast_async(((t_cmd_ast *)ast.pipes.elems)[i],
				session, error))
				return (false);
		}
		i++;
	}
	close(input);
	return (true);
}

void	wait_pipeline(t_pipe_ast ast, pid_t *pids, t_session *session)
{
	t_u32	i;
	int		wstatus;

	i = 0;
	while (i < ast.pipes.size)
	{
		waitpid(pids[i], &wstatus, 0);
		i++;
	}
	if (WIFEXITED(wstatus))
		session->last_status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
		session->last_status = 128 + WTERMSIG(wstatus);
}

bool	execute_pipe_ast(
	t_pipe_ast ast, t_session *session, enum e_exec_error *error
) {
	pid_t	*pids;

	if (ast.pipes.size == 1)
		return (!execute_cmd_ast_sync(((t_cmd_ast *)ast.pipes.elems)[0],
			session, error));
	if (!ft_mem_malloc(&pids, ast.pipes.size * sizeof(pid_t)))
	{
		*error = EXEC_ERROR_EXIT;
		return (false);
	}
	start_pipeline(ast, pids, session, error);
	wait_pipeline(ast, pids, session);
	free(pids);
	ft_oprintln(ft_stderr(), "Status: {u8}", session->last_status);
	return (true);
}

void	free_pipe_ast(t_pipe_ast ast)
{
	t_u32	i;

	i = 0;
	while (i < ast.pipes.size)
	{
		free_cmd_ast(((t_cmd_ast *)ast.pipes.elems)[i]);
		i++;
	}
	ft_vector_free(ast.pipes);
}
