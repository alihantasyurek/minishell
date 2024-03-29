/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:24:23 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/23 17:22:36 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	remove_quotes_in_str(char *str)
{
	int		i;
	int		j;
	int		in_quotes;
	char	quote_char;

	i = 0;
	j = 0;
	in_quotes = 0;
	quote_char = '\0';
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && (!in_quotes
				|| quote_char == str[i]))
		{
			in_quotes = !in_quotes;
			if (in_quotes)
				quote_char = str[i];
			else
				quote_char = '\0';
		}
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

static void	remove_quotes_in_parse(t_parse *parse)
{
	char	**text_ptr;

	if (parse != NULL)
	{
		if (parse->cmd != NULL)
			remove_quotes_in_str(parse->cmd);
		if (parse->text != NULL)
		{
			text_ptr = parse->text;
			while (*text_ptr != NULL)
			{
				remove_quotes_in_str(*text_ptr);
				text_ptr++;
			}
		}
		remove_quotes_in_parse(parse->next);
	}
}

static	void	mini_parse(t_list *lex, t_mini *m_mini, int a[2], char *str)
{
	t_parse	*parse;

	parse = parse_init((size_t)ft_lstsize(lex));
	m_mini->parse = parse;
	while (lex != NULL)
	{
		str = lex->content;
		if (a[0]++ == 0 && ft_strcmp(str, "<<"))
			parse->cmd = ft_strdup(str);
		else if (str[0] == '|' || str[0] == '>' || str[0] == '<')
		{
			if (tokenize_type_for_meta(&parse, str), str[0] == '|')
				a[0] = 0;
			parse->next = parse_init((size_t)ft_lstsize(lex));
			a[1] = 0;
			remove_quotes_in_parse(parse);
			parse = parse->next;
		}
		else
			parse_text_m(parse, str, &a[1]);
		remove_quotes_in_parse(parse);
		lex = lex->next;
	}
}

int	pre_parser(t_mini *m_mini)
{
	int		a[2];
	char	*content;

	content = NULL;
	a[0] = 0;
	a[1] = 0;
	mini_parse(m_mini->lex_list->lex, m_mini, a, content);
	proper_free(&m_mini->lex_list->lex);
	return (create_files_for_meta(m_mini));
}
