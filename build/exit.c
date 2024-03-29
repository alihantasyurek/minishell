/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:21:23 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/24 02:18:28 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>

static int	is_numeric(char *s)
{
	if (s == NULL)
		return (-1);
	while ((9 <= *s && *s <= 13) || *s == 32)
		s++;
	if (*s == 43 || *s == 45)
		s++;
	while (48 <= *s && *s <= 57)
		s++;
	while ((9 <= *s && *s <= 13) || *s == 32)
		s++;
	if (*s != '\0')
		return (0);
	return (1);
}

void	builtin_exit(t_mini **m_mini)
{
	int	status;
	int	exit_value;

	printf("exit\n");
	status = is_numeric((*m_mini)->parse->text[0]);
	if (status == -1)
		exit_value = EXIT_SUCCESS;
	else if (status == 0)
	{
		printf("bash: exit: %s: numeric argument required\n",
			(*m_mini)->parse->text[0]);
		exit_value = 255;
	}
	else if (status == 1 && !(*m_mini)->parse->text[1])
		exit_value = ft_atoi((*m_mini)->parse->text[0]);
	else
	{
		printf("bash: exit: too many arguments\n");
		(*m_mini)->exec_status = 1;
		return ;
	}
	(free_loop(1, *m_mini), free_(*m_mini));
	(free((*m_mini)->lex_list), free(*m_mini));
	exit(exit_value);
}
