/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atasyure <atasyure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:53:35 by aatasyure         #+#    #+#             */
/*   Updated: 2024/03/14 20:04:13 by atasyure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*h;
	const char	*n;
	size_t		counter;

	if (!needle[0])
		return ((char *)haystack);
	while (*haystack && len > 0)
	{
		h = haystack;
		n = needle;
		counter = 0;
		while (n[counter] == h[counter] && n[counter] && len - counter > 0)
			counter++;
		if (n[counter] == '\0')
			return ((char *) haystack);
		len--;
		haystack++;
	}
	return (NULL);
}
