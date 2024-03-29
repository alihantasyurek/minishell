/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:21:30 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/24 00:22:11 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

void	run_echo(t_parse *data, int *i)
{
	int	x;

	x = *i;
	while (data->text[x])
	{
		write(data->outfile, data->text[x], ft_strlen(data->text[x]));
		if (data->text[x + 1] != NULL)
			write(data->outfile, " ", 1);
		x++;
		*i += 1;
	}
}

static int	all_n_chars(const char *str)
{
	while (*str != '\0')
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

void	exec_echo(t_parse *data, t_mini *m_mini)
{
	int	i;

	i = 0;
	if (!data->text)
		write(data->outfile, "\n", 1);
	else if (!data->text || data->text[0] == NULL || data->text[0][0] == '\0')
		write(data->outfile, "\n", 1);
	else
	{
		if (data->text[0][0] == '-' && data->text[0][1] == 'n'
			&& all_n_chars(data->text[0] + 2))
		{
			i = 1;
			if (data->text[1])
				run_echo(data, &i);
		}
		else
		{
			run_echo(data, &i);
			if (!data->text[i])
				write(data->outfile, "\n", 1);
		}
	}
	m_mini->exec_status = 0;
}
