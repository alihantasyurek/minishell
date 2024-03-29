/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emmodogl <rootkalixox@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 01:06:02 by emmodogl          #+#    #+#             */
/*   Updated: 2024/03/18 01:52:05 by emmodogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

int	is_space(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
		return (0);
	return (1);
}

int	print_error(void)
{
	printf("minishell syntax error\n");
	return (0);
}
