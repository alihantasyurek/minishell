/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:23:46 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/23 17:40:21 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

static	int	ignore_quote(char const *cmd, int i)
{
	if (cmd[i] == '\"')
	{
		i++;
		while (cmd[i] != '\"')
			i++;
	}
	else if (cmd[i] == '\'')
	{
		i++;
		while (cmd[i] != '\'')
			i++;
	}
	return (i);
}

static int	len_for_separate(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd || !*cmd)
		return (0);
	if (cmd[i] == '<' && cmd[i + 1] == '<')
		return (2);
	if (cmd[i] == '>' && cmd[i + 1] == '>')
		return (2);
	if (cmd[i] == '<' || cmd[i] == '>' || cmd[i] == '|')
		return (1);
	while (cmd[i] && cmd[i] != ' ' && cmd[i] != '>' && cmd[i] != '<'
		&& cmd[i] != '|')
	{
		if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			i = ignore_quote(cmd, i) + 1;
		}
		else
			i++;
	}
	return (i);
}

void	lexer(char *cmd, t_lexer **lex_list)
{
	int		len;
	char	*content;

	if (!cmd || !*cmd)
		return ;
	cmd = ft_strtrim(cmd, " ");
	len = len_for_separate(cmd);
	content = ft_substr(cmd, 0, len);
	ft_lstadd_back(&(*lex_list)->lex, ft_lstnew(content));
	lexer(cmd + len, lex_list);
	free(cmd);
}
