/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:01:27 by kharuya           #+#    #+#             */
/*   Updated: 2025/01/17 17:11:38 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*ans;
	size_t	s1_len;
	int		i;

	s1_len = ft_strlen(s);
	ans = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!ans)
		return (NULL);
	i = -1;
	while (s[++i])
		ans[i] = s[i];
	ans[i] = '\0';
	return (ans);
}

char	*ft_strchr(const char *src, int c)
{
	char	*s;

	if (!src)
		return (NULL);
	s = (char *)src;
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if (*s == (char)c)
		return (s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ans;
	char	*ans_cpy;

	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		ans = (char *)malloc(sizeof(char) * (len + 1));
		if (ans == NULL)
			return (NULL);
		ans_cpy = ans;
		while (*s1)
			*(ans_cpy++) = *(s1++);
		while (*s2)
			*(ans_cpy++) = *(s2++);
		*ans_cpy = '\0';
		return (ans);
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	sub_len;
	size_t	i;

	if (!s)
		return (NULL);
	sub_len = ft_strlen(s);
	if (sub_len <= start)
	{
		substr = (char *)malloc(sizeof(char) * 1);
		if (substr == NULL)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (sub_len < start + len)
		len = sub_len - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = -1;
	while (++i < len && s[start + i])
		substr[i] = s[start + i];
	substr[i] = '\0';
	return (substr);
}
