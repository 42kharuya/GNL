#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
	int     fd;
	char    *res;
	//  int fd2,fd3; //3つのファイルを指定するために、fdを３つ宣言しておく
	//  size_t i;

	fd = open("test/test4.txt", O_RDONLY);//fd はopen関数の戻り値
	while (1)
	{
		res = get_next_line(fd);
		if (!res)
		{
			printf ("res : %s\n", res);
			break;
		}
		printf ("res : %s", res);
		free (res);
	}
	close(fd);
	return (0);
}