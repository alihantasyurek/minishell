/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:21:55 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/24 02:14:42 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <fcntl.h>

static	void	other_out_files_meta(t_parse *parse, t_mini *m_mini)
{
	char	*pwd1;
	t_parse	*nparse;
	char	*home;

	home = get_env(m_mini->env, "HOME");
	pwd1 = NULL;
	nparse = parse->next;
	if (!ft_strnstr(nparse->text[0], home, ft_strlen(home)))
		handle_relative_path(&pwd1, parse);
	else
		pwd1 = ft_strdup(nparse->text[0]);
	if (nparse->type == GREATER)
		parse->fd = open(pwd1, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (nparse->type == GREAT)
		parse->fd = open(pwd1, O_CREAT | O_RDWR | O_TRUNC, 0777);
	parse->outfile = parse->fd;
	if (pwd1)
		free(pwd1);
	free(home);
}

static void	other_text_create_meta(t_parse *current_parse, t_mini *m_mini)
{
	t_parse	*n_parse;
	int		i;
	int		j;

	n_parse = current_parse->next;
	i = 0;
	while (current_parse->text[i])
		i++;
	while (n_parse && n_parse->type != 2)
	{
		j = 1;
		while (n_parse->text[j])
		{
			current_parse->text[i] = ft_strdup(n_parse->text[j]);
			i++;
			j++;
		}
		n_parse = n_parse->next;
	}
	current_parse->text[i] = NULL;
	other_out_files_meta(current_parse, m_mini);
}

static	void	create_out_files_meta(t_parse *current_parse,
		t_parse *first_parse, t_mini *m_mini)
{
	char	*pwd;
	t_parse	*m_next;
	char	*home;

	home = get_env(m_mini->env, "HOME");
	m_next = current_parse->next;
	if ((m_next->type == GREAT || m_next->type == GREATER))
		return (free(home), other_text_create_meta(current_parse, m_mini));
	if (!ft_strnstr(m_next->text[0], home, ft_strlen(home)))
		handle_relative_path(&pwd, current_parse);
	else
		pwd = ft_strdup(m_next->text[0]);
	if (current_parse->type == GREATER)
		m_next->fd = open(pwd, O_CREAT | O_RDWR | O_APPEND, 0777);
	else if (current_parse->type == GREAT)
		m_next->fd = open(pwd, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (current_parse->cmd)
		current_parse->outfile = m_next->fd;
	else if (first_parse->cmd)
		first_parse->outfile = m_next->fd;
	if (pwd)
		free(pwd);
	free(home);
}

int	create_files_for_meta(t_mini *m_mini)
{
	t_parse	*current_parse;
	t_parse	*first_parse;
	int		i;

	i = 1;
	current_parse = m_mini->parse;
	first_parse = m_mini->parse;
	while (current_parse)
	{
		if (current_parse->type == GREAT || current_parse->type == GREATER)
			create_out_files_meta(current_parse, first_parse, m_mini);
		else if (current_parse->type == LESS)
			i = create_in_files_meta(current_parse, m_mini);
		current_parse = current_parse->next;
	}
	return (i);
}
