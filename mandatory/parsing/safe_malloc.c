/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:12:47 by klamachi          #+#    #+#             */
/*   Updated: 2025/10/10 14:31:25 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*safe_strjoin(char const *s1, char const *s2)
{
	char	*p;
	char	*st;

	if (!s2)
		s2 = safe_strdup("");
	p = safe_malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	st = p;
	while (*s1)
	{
		*p = *s1;
		p++;
		s1++;
	}
	while (*s2)
	{
		*p = *s2;
		p++;
		s2++;
	}
	*p = '\0';
	return (st);
}

char	*safe_strdup(const char *s)
{
	char	*str;
	size_t	i;

	str = safe_malloc(ft_strlen(s) + 1);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*safe_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
	{
		p = safe_malloc(1);
		p[0] = '\0';
		return (p);
	}
	if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	p = safe_malloc((len + 1) * sizeof(char));
	i = 0;
	while (i < len)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
