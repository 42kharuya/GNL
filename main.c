#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
	int     fd;
	char    *res1;
	char    *res2;
	//  int fd2,fd3; //3つのファイルを指定するために、fdを３つ宣言しておく
	//  size_t i;

	fd = open("test/test1.txt", O_RDONLY);//fd はopen関数の戻り値
	// fd2 = open("text2.txt", O_RDONLY);//別ファイルには別のfd値が格納される
	// fd3 = open("text3.txt", O_RDONLY);//別ファイルには別のfd値が格納される
	res1 = get_next_line(fd);
	if (!res1)
	{
		printf ("res1:%s", res1);
		return (0);
	}
	res2 = get_next_line(fd);
	if (!res2)
	{
		printf ("res2:%s", res2);
		return (0);
	}
	printf("%s", res1);
	printf("%s", res2);
	free (res1);
	free (res2);
	// printf("%s", get_next_line(fd2));
	// printf("%s", get_next_line(fd3));
	close(fd);
	return (0);
}