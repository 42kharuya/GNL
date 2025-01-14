#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
	int     fd;
	char    *res1;
	//  int fd2,fd3; //3つのファイルを指定するために、fdを３つ宣言しておく
	//  size_t i;

	fd = open("test/test1.txt", O_RDONLY);//fd はopen関数の戻り値
	res1 = get_next_line(fd);
	if (!res1)
	{
		printf ("%s\n", res1);
		return (0);
	}
	printf ("out of if :%s\n", res1);
	free (res1);
	close(fd);
	return (0);
}