/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:47:02 by emmodogl          #+#    #+#             */
/*   Updated: 2024/03/24 01:37:28 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	int	unset_edit(t_list **node, t_list **prev_node, t_mini *m_mini)
{
	t_env	*tmp;

	tmp = (*node)->content;
	if (*prev_node == NULL)
		m_mini->env = (*node)->next;
	else
		(*prev_node)->next = (*node)->next;
	free(tmp->key);
	if (tmp->value)
		free(tmp->value);
	free((*node)->content);
	free(*node);
	return (1);
}

void	exec_unset(t_parse *data, t_mini *m_mini, int i, int x)
{
	t_list	*prev_node;
	t_list	*node;
	t_env	*env;

	env = NULL;
	if (data->text == NULL)
		return ;
	while (data->text[i])
	{
		prev_node = NULL;
		node = m_mini->env;
		while (node != NULL)
		{
			env = (t_env *)node->content;
			if (ft_strcmp(env->key, data->text[i]) == 0)
				x = unset_edit(&node, &prev_node, m_mini);
			if (x)
				break ;
			prev_node = node;
			node = node->next;
		}
		i++;
	}
}
