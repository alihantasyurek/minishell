/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 23:21:08 by emmodogl          #+#    #+#             */
/*   Updated: 2024/03/24 01:05:07 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void	exec_cd1(char *str, t_parse *data, t_mini *m_mini)
{
	change_old(str, m_mini);
	chdir(get_home(m_mini));
	change_pwd(data, m_mini);
	m_mini->exec_status = 0;
}

void	exec_cd(t_parse *data, t_mini *m_mini)
{
	char	*str;
	char	*err;

	str = getcwd(NULL, 0);
	if (data->text && data->text[0])
	{
		if (chdir(data->text[0]) == 0)
		{
			change_old(str, m_mini);
			change_pwd(data, m_mini);
			m_mini->exec_status = 0;
		}
		else
		{
			err = strerror(errno);
			printf("minishell: %s\n", err);
			m_mini->exec_status = 1;
		}
	}
	else
		exec_cd1(str, data, m_mini);
	free(str);
}
