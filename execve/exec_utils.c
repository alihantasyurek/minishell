/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:22:27 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/23 23:58:33 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_parse	*_next_command(t_parse **parse)
{
	if ((*parse)->infile > STDERR || (*parse)->outfile > STDERR
		|| (*parse)->type == HEREDOC)
	{
		return ((*parse)->next->next);
	}
	else
	{
		return ((*parse)->next);
	}
}

int	pipe_counter(t_mini *m_mini)
{
	t_parse	*parse;
	int		i;

	i = 0;
	parse = m_mini->parse;
	while (parse)
	{
		if (parse->type == PIPE)
			i++;
		parse = parse->next;
	}
	return (i);
}

void	multi_command_next(t_parse **parse)
{
	if ((*parse)->type == HEREDOC || (*parse)->infile > STDERR
		|| (*parse)->outfile > STDERR)
		*parse = (*parse)->next->next;
	else
		*parse = (*parse)->next;
}
