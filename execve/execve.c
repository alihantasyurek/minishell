/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atasyure <atasyure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:22:44 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/23 22:44:13 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>
#include <unistd.h>

static char	*search_command(char *cmd, char **value)
{
	char	*data;
	size_t	length;
	char	*substring;
	char	*tmp;

	substring = NULL;
	data = NULL;
	tmp = *value;
	while (*tmp && *tmp != ':')
		tmp++;
	length = tmp - *value;
	if (!length)
		return (NULL);
	substring = ft_substr(*value, 0, length);
	data = ft_strjoin(substring, "/");
	free(substring);
	substring = ft_strjoin(data, cmd);
	free(data);
	if (*tmp)
		*value = tmp + 1;
	return (substring);
}

static	char	*_search_path(t_mini *m_mini)
{
	t_env	*env;
	t_list	*tmp;
	char	*value;

	value = NULL;
	tmp = m_mini->env;
	while (tmp)
	{
		env = tmp->content;
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			value = env->value;
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static	void	search_path(t_parse *data, int i, t_mini *m_mini)
{
	char	*value;
	char	*str;
	int		x;

	x = -1;
	str = NULL;
	value = _search_path(m_mini);
	while (x != 0 && value && ++i < 10)
	{
		if (str)
			free(str);
		str = search_command(data->cmd, &value);
		if (str)
			x = access(str, F_OK);
		if (str && x == 0)
		{
			free(data->cmd);
			data->cmd = ft_strdup(str);
		}
	}
	free(str);
}

void	run_execve(t_parse *parse, char **env, int *fd, t_mini *m_mini)
{
	char	**full_cmd;

	search_path(parse, -1, m_mini);
	parse->pid = fork();
	full_cmd = NULL;
	if (parse->pid == 0)
	{
		full_cmd = get_args(parse, 0);
		create_dup(m_mini, parse);
		if (!full_cmd || !parse->cmd || (execve(parse->cmd, full_cmd, env)
				== -1))
		{
			if (parse->cmd && ft_strcmp(parse->cmd, "<<"))
				write (2, "minishell: command not found\n", 29);
			execve_child_free(full_cmd, m_mini);
			exit(127);
		}
	}
	if (fd && parse->pid)
		clear_pipe(fd);
	waitpid(parse->pid, &m_mini->exec_status, 0);
	m_mini->exec_status = WEXITSTATUS(m_mini->exec_status);
}

void	exec_others(t_parse *parse, char **env, int *fd, t_mini *m_mini)
{
	g_heredoc_sig = -2;
	run_execve(parse, env, fd, m_mini);
}
