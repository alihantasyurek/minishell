/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:24:39 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/24 01:32:26 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>
#include <unistd.h>

void	wait_all(t_mini *m_mini)
{
	t_parse	*data;

	data = m_mini->parse;
	while (data)
	{
		if (!data->next)
			waitpid(data->pid, &m_mini->exec_status, 0);
		else
			waitpid(data->pid, 0, 0);
		data = data->next;
	}
	m_mini->exec_status = WEXITSTATUS(m_mini->exec_status);
}

void	clear_pipe(int *fd)
{
	int	index;

	if (fd)
	{
		index = -1;
		while (++index < 2)
		{
			if (fd[index])
				close(fd[index]);
		}
		if (fd)
			free(fd);
	}
}

void	ft_newlstiter(t_list *lst, void (*f)(void *, t_mini *), t_mini *mini)
{
	if (!(lst || f))
		return ;
	while (lst != NULL)
	{
		f(lst->content, mini);
		lst = lst->next;
	}
}
