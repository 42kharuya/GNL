/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:01:30 by kharuya           #+#    #+#             */
/*   Updated: 2025/01/13 04:54:55 by kharuya          ###   ########.fr       */
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

static char *make_line(char **save, ssize_t count_byte)
{
	char *result;

	if (count_byte == 0)
	{
		if(!save)
			return (null_free(save));
		return (*save);
	}
	result = *save;
	*save =  ft_substr(*save, count_byte + 1, BUFFER_SIZE);
	if (!save)
		return (null_free(save));
	// ↓文字列の途中でNULL文字入れてしまう問題
	result[count_byte + 1] = '\0';
	return (result);
}

static char *gnl_read(int fd, char *buffer, char **save)
{
	ssize_t count_byte;
	char 	*tmp;

	count_byte = 0;
	tmp = NULL;
	while (ft_strchr(*save, '\n') == NULL)
	{
		count_byte = read(fd, buffer, BUFFER_SIZE);
		printf ("save: %s buffer: %s\n", *save, buffer);
		if (count_byte == -1)
			return (null_free (save));
		else if (count_byte == 0)
			return (make_line(save, count_byte));
		tmp = ft_strjoin(*save, buffer);
		if (!tmp)
			return (null_free(save));
		null_free (save);
		*save = tmp;
	}
	// ↓tmpのfree問題
	return (make_line(save, ft_strchr(tmp, '\n') - tmp + 1));
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


// ↓この問題を解決する
// freeしなきゃいけない変数
// save, buffer, tmp

// BUFFER_SIZEが読み込む行のバイト数よりも大きい場合
// →'\n'で切る
// BUFFER_SIZEが読み込む行のバイト数よりも小さい場合
// →BUFFER_SIZEで切る

// 現段階フェーズ:単一1行読み込み


// 1文字のみreadする関数
// char *get_next_line(int fd)
// {
// 	char	*buf;

// 	if (!fd)
// 		return (NULL);
// 	buf = (char *)malloc(sizeof(char) * 2);
// 	if (read(fd, &buf[0], 1) == -1)
// 	{
// 		free (buf);
// 		return (NULL);
// 	}
// 	buf[1] = '\0';
// 	return (buf);
// }
