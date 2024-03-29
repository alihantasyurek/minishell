/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:22:07 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/24 02:08:09 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>
#include <stdio.h>

static	void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	env_get(char **env, t_mini **mini)
{
	t_env	*key_v;
	char	**str;

	while (*env)
	{
		key_v = malloc(sizeof(t_env));
		if (!key_v)
			return (printf(A_ERR), 1);
		str = ft_split(*env, '=');
		key_v->key = NULL;
		if (str[0] != NULL)
			key_v->key = ft_strdup(str[0]);
		key_v->value = NULL;
		if (str[1] != NULL)
			key_v->value = ft_strdup(str[1]);
		ft_lstadd_back(&(*mini)->env, ft_lstnew(key_v));
		free_str(str);
		env++;
	}
	return (0);
}
