/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:01:30 by kharuya           #+#    #+#             */
/*   Updated: 2025/01/14 19:06:43 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char *null_free(char **save)
{
	free (*save);
	*save = NULL;
	return (NULL);
}

static char *make_ans(char *pre_ans, ssize_t count_byte)
{
	char *ans;
	int i;

	ans = (char *)malloc(sizeof(char) * (count_byte + 1));
	if (!ans)
		return (NULL);
	i = -1;
	while (++i < count_byte)
		ans[i] = pre_ans[i];
	ans[count_byte] = '\0';
	return (ans);
}

static char *make_line(char **save, char *pre_ans, ssize_t count_byte)
{
	char *result;

	if (count_byte == 0)
	{
		if(**save == '\0')
			return (null_free(save));
		null_free (save);
		return (pre_ans);
	}
	result = make_ans(pre_ans, count_byte);
	if (!result)
		return (NULL);
	*save =  ft_substr(pre_ans, count_byte, BUFFER_SIZE);
	if (!(*save))
		return (null_free(save));
	return (result);
}

static char *gnl_read(int fd, char *buffer, char **save)
{
	ssize_t count_byte;
	char 	*pre_ans;

	count_byte = 0;
	pre_ans = *save;
	while (ft_strchr(pre_ans, '\n') == NULL)
	{
		count_byte = read(fd, buffer, BUFFER_SIZE);
		if (count_byte == -1)
			return (null_free (save));
		else if (count_byte == 0)
			return (make_line(save, pre_ans, count_byte));
		pre_ans = ft_strjoin(pre_ans, buffer);
		if (!pre_ans)
			return (null_free(save));
	}
	return (make_line(save, pre_ans, ft_strchr(pre_ans, '\n') - pre_ans + 1));
}

char *get_next_line(int fd)
{
	static	char	*save;
	char 			*buffer;
	char			*result;

	if(!fd || BUFFER_SIZE <= 0)
		return (NULL);
	if(!save)
	{
		save = ft_strdup("");
		if(!save)
			return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	result = gnl_read(fd, buffer, &save);
	free (buffer);
	return (result);
}


// テスター通してエラー発生のため、ここに対して修正する