#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
	int     fd;
	char    **res1;
	//  int fd2,fd3; //3つのファイルを指定するために、fdを３つ宣言しておく
	//  size_t i;

	fd = open("test/test1.txt", O_RDONLY);//fd はopen関数の戻り値
	close(fd);
	return (0);
}