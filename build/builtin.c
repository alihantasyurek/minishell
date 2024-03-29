/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:20:31 by aatasyure         #+#    #+#             */
/*   Updated: 2024/03/24 01:49:50 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

static void	make_lowercase(char *string)
{
	int	c;

	c = 0;
	while (string[c] != '\0')
	{
		if (string[c] >= 'A' && string[c] <= 'Z')
			string[c] += 32;
		c++;
	}
}

int	execute_builtin_command(t_parse *parse, t_mini *m_mini)
{
	char	*temp;
	int		len;

	len = ft_strlen(parse->cmd) + 1;
	temp = malloc(sizeof(char) * len);
	ft_strlcpy(temp, parse->cmd, len);
	make_lowercase(temp);
	if ((ft_strcmp(temp, "echo") == 0))
		return (free(temp), exec_echo(parse, m_mini), 1);
	if (ft_strcmp(temp, "cd" ) == 0)
		return (free(temp), exec_cd(parse, m_mini), 1);
	if ((ft_strcmp(temp, "pwd") == 0))
		return (free(temp), exec_pwd(parse, m_mini), 1);
	if ((ft_strcmp(temp, "env") == 0))
		return (free(temp), exec_env(m_mini), 1);
	free(temp);
	if (ft_strcmp(parse->cmd, "export") == 0)
		return (exec_export(parse, m_mini), 1);
	if (ft_strcmp(parse->cmd, "unset") == 0)
		return (exec_unset(parse, m_mini, 0, 0), 1);
	return (0);
}

void	edit_env(t_list *node, char *key, char *value, t_mini *m_mini)
{
	t_env	*env;

	while (node != NULL)
	{
		env = (t_env *)node->content;
		if (ft_strcmp(env->key, key) == 0)
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(value);
			if (value)
				free(value);
			free(key);
			return ;
		}
		node = node->next;
	}
	edit_env_(node, key, value, m_mini);
}
