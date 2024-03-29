/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atasyure <atasyure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:21:43 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/23 22:40:17 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

static int	is_valid_other(char *a, char *b)
{
	if (((a[0] == '>' || a[0] == '<') && !a[1]) && b[0] == a[0])
	{
		return (0);
	}
	else if (((a[0] == '>' && a[1] == '>')) && (!ft_strcmp(a, b)))
		return (0);
	else if (((a[0] == '<' && a[1] != '<')) && (b[0] == '<' || b[0] == '>'
			|| b[0] == '|'))
		return (0);
	else if ((a[0] == '>' && a[1] != '>') && (b[0] == '<' || b[0] == '>'
			|| b[0] == '|'))
		return (0);
	else if (((a[0] == '<' && a[1] == '<')) && (b[0] == '>' || b[0] == '|'))
		return (0);
	else if ((a[0] == '>' && a[1] == '>') && (b[0] == '<' || b[0] == '>'
			|| b[0] == '|'))
		return (0);
	else if ((a[0] == '|' && !a[1] && b[0] == '|' && !b[1]))
		return (0);
	return (1);
}

int	cmd_is_valid(t_lexer *lex_list, int i)
{
	t_list	*tmp;
	char	*a;
	char	*b;

	b = NULL;
	tmp = lex_list->lex;
	while (tmp)
	{
		a = tmp->content;
		if (tmp->next)
			b = tmp->next->content;
		if (i == 0 && !b && ((a[0] == '<') || (a[0] == '>')))
			return (print_error());
		else if ((a[0] == '|' && !a[1]) && i == 0)
			return (print_error());
		else if (((a[0] == '>' || a[0] == '<') && !a[1]) && !b)
			return (print_error());
		else if ((a[0] == '<' && a[1] == '<' && b[0] == '<'))
			return (print_error());
		else if (!is_valid_other(a, b))
			return (print_error());
		tmp = tmp->next;
		i++;
	}
	return (1);
}

int	quote_control(char *data)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] == '\'' || data[i] == '\"')
		{
			j++;
			c = data[i++];
			while (data[i] && data[i] != c)
				i++;
			if (!data[i])
				break ;
			j++;
		}
		i++;
	}
	if (j % 2 != 0)
		return (printf("minishell: quote error\n"), 0);
	return (1);
}
