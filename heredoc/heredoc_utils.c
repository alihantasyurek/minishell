/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:23:31 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/24 02:12:54 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <sys/ioctl.h>

void	killer(int sig)
{
	(void)sig;
	g_heredoc_sig = -3;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	set_heredoc(int sig)
{
	(void)sig;
	g_heredoc_sig = -10;
}
