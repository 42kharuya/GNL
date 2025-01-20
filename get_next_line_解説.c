/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_解説.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:01:30 by kharuya           #+#    #+#             */
/*   Updated: 2025/01/18 16:22:31 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*null_free(char **save)
{
	free (*save);
	//freeしたsaveにNULLを再度入れることで再初期化する
	//ダングリングポインタを使用しないようにするため(予期せぬ動作を引き起こす)
	//ダングリングポインタとは解放された解放されたメモリ領域を指すポインタのこと
	*save = NULL;
	return (NULL);
}

//make_ans関数は\nまでの文字列を切り出す
static	char	*make_ans(char *save, ssize_t count_byte)
{
	char	*ans;
	int		i;

	ans = (char *)malloc(sizeof(char) * (count_byte + 1));
	if (!ans)
		return (NULL);
	i = -1;
	//saveの文字列をcount_byte分までansに格納することで\nまでの文字列を切り出せる
	while (++i < count_byte)
		ans[i] = save[i];
	ans[count_byte] = '\0';
	return (ans);
}

//make_line関数は粗読み込みした文字列saveから\nまでの文字列を取り出すとともに余剰分を静的変数saveに代入する。
static	char	*make_line(char **save, ssize_t count_byte)
{
	char	*ans;
	char	*tmp;

	//以下二つの場合の処理
	//①ファイルに何も入っていない
	//②ファイルの末端に達した
	if (count_byte == 0)
	{
		//①の場合の処理
		if (**save == '\0')
			return (null_free(save));
		//②の場合の処理
		//ansにsaveの内容をコピーした上で、saveをfreeして、メモリリークを防ぐ
		ans = ft_strdup(*save);
		null_free (save);
		return (ans);
	}

	//ansに\nまでの文字列を格納する
	ans = make_ans(*save, count_byte);
	if (!ans)
		return (null_free(save));

	//　\n以降の文字列をsaveに格納するために一時的にtmpに代入する
	tmp = ft_substr(*save, count_byte, BUFFER_SIZE);
	if (!tmp)
		return (null_free(save));
	//	saveにtmpの内容を代入するために一度saveに保存されているテキストをfreeする。
	null_free (save);
	*save = tmp;
	return (ans);
}

static	char	*gnl_read(int fd, char *buffer, char **save)
{
	ssize_t	count_byte;
	char	*tmp;

	//saveに保存したテキストの中に\nを検知するまでwhile文を回してバイトを読み込む
	while (ft_strchr(*save, '\n') == NULL)
	{
		//bufferにBUFFER_SIZE分読み込んで代入する。返り値は読み込んだ実際に読み込んだバイト数
		//読み込めるバイト数がBUFFER_SIZE未満の場合は読み込める分だけ読み込む
		count_byte = read(fd, buffer, BUFFER_SIZE);

		//-1はエラー
		if (count_byte == -1)
			return (null_free (save));

		//0はファイルの末端に達したかあるいはファイルに何も入っていない
		else if (count_byte == 0)
			return (make_line(save, count_byte));
		// bufferの末尾にNULL終端を付記
		buffer[count_byte] = '\0';

		//前回読み込んだ\n以降の余剰分を先頭にしてbufferで読み込んだテキストを連結していく。
		//tmpのエラー処理やsaveのfree処理を行うために一度tmpに代入する
		tmp = ft_strjoin(*save, buffer);

		//NULL処理
		//エラー処理なのでsaveをfreeして、メモリリークを防ぐ
		if (!tmp)
			return (null_free(save));

		//saveにtmpを代入する前に、一度saveをfreeしてリセットすることでメモリリークを防ぐ
		null_free(save);
		//tmpの内容をsaveに代入する。
		*save = tmp;
	}

	//　strchr関数をつかってsaveの改行部分のポインタとsaveポインタの差分で文字列がわかる(+1は\n文字分)
	return (make_line(save, ft_strchr(*save, '\n') - *save + 1));
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buffer;
	char		*result;

	//ファイルディスクリプタ取得時にエラーが発生した
	//read関数で読み取るBUFFER_SIZEが0以下で読み込めない
	//上記の場合にエラーとしてNULLを返す
	//[注意]ファイルディスクリプタの上限を設定しないのは、OS依存性があるため、値が定まらないから
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	//静的変数(static variable)が未定義の場合あるいはNULLの場合にft_strdup関数で空の文字列を代入して初期化
	if (!save)
	{
		save = ft_strdup("");
		if (!save)
			return (NULL);
	}
	//read関数で読み取ったBUFFER_SIZE分のテキストを格納するための変数
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);

	//saveがダブルポインタなのはsaveを値渡しではなく参照渡ししたいため。
	result = gnl_read(fd, buffer, &save);

	//使い終わったbufferを解放する
	free (buffer);
	return (result);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*res;

// 	fd = open ("test.txt", O_RDONLY);
// 	printf ("fd : %d\n", fd);
// 	while (1)
// 	{
// 		res = get_next_line(fd);
// 		if (!res)
// 		{
// 			printf ("\nres : n%s", res);
// 			break ;
// 		}
// 		printf ("res : %s", res);
// 		free (res);
// 	}
// 	close(fd);
// 	return (0);
// }
