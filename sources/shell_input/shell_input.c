/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchakhno <vchakhno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 00:38:29 by vchakhno          #+#    #+#             */
/*   Updated: 2024/01/28 09:11:30 by vchakhno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_input.h"
#include "grammar.h"
#include "utils.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

bool	alloc_shell_input(t_shell_input *input)
{
	if (!ft_string_alloc(&input->text, 30))
		return (false);
	input->cursor = 0;
	rl_outstream = stderr;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	return (true);
}

bool	get_incomplete_ast(
	t_shell_input *input, t_ast_root *ast, bool *valid
) {
	t_parsing_status	status;

	if (!alloc_ast(ast))
		return (PARSING_EXITED);
	status = parse_ast(ast, input);
	while (status == PARSING_CANCELED)
	{
		cut_lines(input);
		free_ast(*ast);
		if (!alloc_ast(ast))
			return (PARSING_EXITED);
		status = parse_ast(ast, input);
	}
	*valid = status == PARSING_SUCCEEDED;
	return (status != PARSING_EXITED);
}

// true -> continue
// false -> exit
bool	get_complete_ast(t_shell_input *input, t_ast_root *ast)
{
	bool	complete;

	complete = false;
	while (!complete)
	{
		if (!get_incomplete_ast(input, ast, &complete))
			return (false);
		if (!complete)
			print_error("Syntax error");
		register_command(*input);
		cut_lines(input);
	}
	return (true);
}

void	free_shell_input(t_shell_input input)
{
	ft_string_free(input.text);
	clear_history();
}
