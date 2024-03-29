/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:24:14 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/23 17:16:57 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

void	parse_text_m(t_parse *parse, char *str, int *j)
{
	parse->text[*j] = ft_strdup(str);
	*j += 1;
	parse->text[*j] = NULL;
}

void	flag_free(t_parse *parse)
{
	free_text(parse->text);
	parse->text = NULL;
}

void	tokenize_type_for_meta(t_parse **parse, const char *str)
{
	if (str[0] == '|')
		(*parse)->type = PIPE;
	else if (str[0] == '>' && str[1] == '>')
		(*parse)->type = GREATER;
	else if (str[0] == '<' && str[1] == '<')
	{
		(*parse)->type = HEREDOC;
		g_heredoc_sig = 1;
	}
	else if (str[0] == '>')
		(*parse)->type = GREAT;
	else if (str[0] == '<')
		(*parse)->type = LESS;
}

t_parse	*parse_init(size_t len)
{
	t_parse	*parse;

	parse = ft_calloc(1, sizeof(t_parse));
	if (!parse)
		return (NULL);
	(parse)->infile = STDIN;
	(parse)->outfile = STDOUT;
	(parse)->fd = 1;
	(parse)->text = ft_calloc(sizeof(char *), len + 1);
	if (!(parse)->text)
		return (free(parse), NULL);
	return (parse);
}
