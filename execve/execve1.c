/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atasyure <atasyure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:22:51 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/23 22:44:05 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

char	**get_args(t_parse *parse, int j)
{
	char	**exec;
	int		i;

	if (parse->text)
		while (parse->text[j])
			j++;
	exec = malloc(sizeof(char *) * (j + 2));
	if (!exec)
		return (NULL);
	i = 0;
	if (parse->cmd == NULL)
		exec[0] = NULL;
	else
		exec[0] = ft_strdup(parse->cmd);
	j = 1;
	if (parse->text)
	{
		while (parse->text[i])
		{
			exec[j] = ft_strdup(parse->text[i++]);
			j++;
		}
	}
	exec[j] = NULL;
	return (exec);
}
