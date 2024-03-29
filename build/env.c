/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:21:16 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/24 01:32:41 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	edit_env_(t_list *node, char *key, char *value, t_mini *m_mini)
{
	t_env	*new_env;

	if (node == NULL)
	{
		new_env = malloc(sizeof(t_env));
		if (!new_env)
			return ;
		new_env->key = key;
		new_env->value = value;
		ft_lstadd_back(&(m_mini->env), ft_lstnew(new_env));
	}
}

char	*get_home(t_mini *m_mini)
{
	t_list	*tmp;
	t_env	*env;

	tmp = m_mini->env;
	while (tmp)
	{
		env = tmp->content;
		if (!ft_strcmp(env->key, "HOME"))
			return (env->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static	void	print_list(void *data, t_mini *m_mini)
{
	t_parse	*str;
	t_env	*new;
	int		i;

	i = 0;
	str = m_mini->parse;
	new = (t_env *)data;
	if (!new->value)
		return ;
	while (new->key[i])
		write(str->outfile, &new->key[i++], 1);
	write(str->outfile, "=", 1);
	i = 0;
	while (new->value && new->value[i])
		write(str->outfile, &new->value[i++], 1);
	write(str->outfile, "\n", 1);
}

void	exec_env(t_mini *m_mini)
{
	ft_newlstiter(m_mini->env, print_list, m_mini);
	m_mini->exec_status = 0;
}
