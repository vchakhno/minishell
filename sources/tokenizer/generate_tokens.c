/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekhaled <ekhaled@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:09:31 by ekhaled           #+#    #+#             */
/*   Updated: 2023/09/21 05:08:57 by ekhaled          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



bool	get_token(t_cstr input, t_token_queue *token_queue)
{
	t_token	token;

	
}

bool	generate_tokens(t_cstr input, t_token_queue *token_queue)
{
	bool	found_heredoc;

	input.cursor = 0;
	found_heredoc = false;
	while (input.str[input.cursor]
		&& (!found_heredoc || (*token_queue)->content.type != NEWLINE_TOKEN))
	{
		get_token(input, token_queue);
	}

}