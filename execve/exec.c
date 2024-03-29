/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:22:38 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/23 23:59:35 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>
#include <unistd.h>

static void	run_command(char **env, t_parse *tmp, int *fd, t_mini *m_mini)
{
	if (execute_builtin_command(tmp, m_mini) == 0)
		exec_others(tmp, env, fd, m_mini);
	free_(m_mini);
	free_loop(1, m_mini);
	free(m_mini->lex_list);
	free(m_mini);
	exit(0);
}

static void	only_single_command(char **env, t_parse *parse, t_mini *m_mini)
{
	if (parse->type != HEREDOC)
		if (execute_builtin_command(m_mini->parse, m_mini))
			return ;
	exec_others(m_mini->parse, env, NULL, m_mini);
}

static	void	multi_command_two(t_parse *parse,
		char **env, t_mini *m_mini, int *fd)
{
	t_parse	*nparse;

	while (parse)
	{
		if (parse->next)
			pipe(fd);
		nparse = _next_command(&parse);
		parse->pid = fork();
		if (parse->pid == 0)
		{
			create_dup_one(parse, fd);
			run_command(env, parse, fd, m_mini);
		}
		if (nparse)
			create_dup_two(nparse, fd);
		parse = nparse;
	}
}

void	multi_command(char **env, t_parse *parse, t_mini *m_mini)
{
	int	*fd;

	m_mini->parse->std_in = dup(0);
	fd = (int *)malloc(sizeof(int) * 2);
	if (!fd)
		return ;
	multi_command_two(parse, env, m_mini, fd);
	dup2(m_mini->parse->std_in, 0);
	clear_pipe(fd);
	wait_all(m_mini);
}

void	exec(char **env, t_mini *m_mini)
{
	int	index;

	if (g_heredoc_sig != 0)
		loop_heredoc(m_mini);
	if (m_mini->parse->cmd && !ft_strcmp(m_mini->parse->cmd, "exit")
		&& g_heredoc_sig != -10 && _next_command(&m_mini->parse) == NULL)
	{
		builtin_exit(&m_mini);
		return ;
	}
	index = pipe_counter(m_mini);
	if (!index && g_heredoc_sig != -10)
		only_single_command(env, m_mini->parse, m_mini);
	else if (g_heredoc_sig != -10)
		multi_command(env, m_mini->parse, m_mini);
	g_heredoc_sig = 0;
}
