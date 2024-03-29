/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:23:06 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/24 01:59:41 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

void	handle_dollar(t_mini *mini, t_list *lex, char **temp, char *before)
{
	if ((*temp)[1] == '?')
		expand_question_mark(mini, lex, temp, before);
	else if ((*temp)[1] != '$' && ft_strcmp((*temp), "$") != 0)
		expand_dollar_variable(mini, lex, temp, before);
	else
		*temp = ft_strchr(*temp + 1, '$');
}

void	expand_dollar_internal(t_mini *mini, t_list *lex)
{
	char	*temp;
	char	*before;

	temp = ft_strchr(lex->content, '$');
	while (temp)
	{
		before = ft_substr(lex->content, 0, temp - (char *)lex->content);
		if (check_quote(before, temp))
			handle_dollar(mini, lex, &temp, before);
		else
			temp = ft_strchr(temp + 1, '$');
		free(before);
	}
}

static void	expand_dollar(t_mini *mini)
{
	t_list	*lex;

	lex = mini->lex_list->lex;
	while (lex)
	{
		expand_dollar_internal(mini, lex);
		lex = lex->next;
	}
}

static void	expand_tilde(t_mini *mini)
{
	t_list	*lex;

	lex = mini->lex_list->lex;
	while (lex)
	{
		if (*((char *)(lex->content)) == '~')
			expander_tilde(mini, lex, NULL);
		lex = lex->next;
	}
}

void	expander(t_mini *mini)
{
	expand_tilde(mini);
	if (mini->cmd[0] == '<' && mini->cmd[1] == '<')
		return ;
	expand_dollar(mini);
}
