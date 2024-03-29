/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:23:25 by atasyure          #+#    #+#             */
/*   Updated: 2024/03/18 01:28:30 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>
#include <stdio.h>

void	free_init_check(t_mini *mini)
{
	if (mini->env)
		free_(mini);
	if (mini)
		free(mini);
	return ((void)printf(ENV_ERR));
}
