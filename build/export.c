/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:20:55 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/24 01:48:53 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static	int	ft_strchrindex_0(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static void	declare_export(void *data, t_mini *m_mini)
{
	t_parse	*str;
	t_env	*new;
	int		i;

	i = 0;
	str = m_mini->parse;
	new = (t_env *)data;
	write(str->outfile, "declare -x ", 11);
	while (new->key[i])
		write(str->outfile, &new->key[i++], 1);
	if (new->value && *(new->value) && new->key[0] > 31)
		write(str->outfile, "=", 1);
	i = 0;
	while (new->value && new->value[i])
		write(str->outfile, &new->value[i++], 1);
	write(str->outfile, "\n", 1);
}

static	int	export_key_control(char *text)
{
	int	i;

	if (text[0] == '=' || ft_isdigit(text[0]))
		return (0);
	i = 0;
	while (text[i] && text[i] != '=' && (ft_isalnum(text[i]) || text[i] == '_'))
		i++;
	if (text[i] == '=' || !text[i])
		return (1);
	return (0);
}

static	int	export_print(char *text, t_mini *m_mini)
{
	char	*key;
	char	*value;

	if (!export_key_control(text))
	{
		write(2, "minishell: export: `", 20);
		write(2, text, ft_strlen(text));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	if (ft_strchrindex_0(text, '=') != -1)
	{
		key = ft_substr(text, 0, ft_strchrindex(text, '='));
		value = ft_substr(text, ft_strchrindex(text, '=') + 1, (ft_strlen(text)
					- 1));
	}
	else
	{
		key = ft_substr(text, 0, ft_strlen(text));
		value = NULL;
	}
	edit_env(m_mini->env, key, value, m_mini);
	return (0);
}

int	exec_export(t_parse *data, t_mini *m_mini)
{
	int	i;

	i = 0;
	if (data->text == NULL)
		ft_newlstiter(m_mini->env, declare_export, m_mini);
	else
	{
		while (data->text[i])
		{
			if (export_print(data->text[i], m_mini))
			{
				m_mini->exec_status = 1;
				return (1);
			}
			i++;
		}
	}
	m_mini->exec_status = 0;
	return (0);
}
