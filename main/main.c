/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:23:53 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/24 02:59:41 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/history.h>
#include <readline/readline.h>

int		g_heredoc_sig;

void	get_readline(t_mini *mini)
{
	mini->cmd = readline("🟢 emmodogl&&aatasyure$ ");
	if (mini->cmd && !is_space(mini->cmd))
	{
		if (ft_strlen(mini->cmd) != 0)
			add_history(mini->cmd);
		free(mini->cmd);
		get_readline(mini);
	}
	else if (!mini->cmd)
	{
		free_loop(0, mini);
		free_(mini);
		free(mini->lex_list);
		free(mini);
		exit(1);
	}
	add_history(mini->cmd);
}

void	parser(t_mini *mini, char **env, int control)
{
	control = cmd_is_valid(mini->lex_list, 0);
	if (!control)
	{
		proper_free(&mini->lex_list->lex);
		free_loop(control, mini);
		return ;
	}
	else
	{
		if (pre_parser(mini))
			exec(env, mini);
	}
	free_loop(control, mini);
}

static	void	start_minishell(t_mini *mini, char **env, int control)
{
	while (42)
	{
		get_readline(mini);
		if (quote_control(mini->cmd))
		{
			lexer(mini->cmd, &mini->lex_list);
			expander(mini);
			parser(mini, env, control);
		}
		else
		{
			(free(mini->cmd));
			continue ;
		}
	}
}

static int	argument_control(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		return (printf(W_ARGS), 1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;

	if (argument_control(argc, argv) != 0)
		return (127);
	if (init(&mini) != 0)
		return (printf(A_ERR), 1);
	if (env_get(env, &mini))
		return (free_init_check(mini), 1);
	signals_control();
	start_minishell(mini, env, 0);
}
