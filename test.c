#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

// int main (void)
// {
// 	// ssize_t count_byte1;
// 	// ssize_t count_byte2;
// 	int 	fd;
// 	char	*res1;
// 	char	*res2;

// 	res1 = (char *)malloc(sizeof(char) * (1 + 1));
// 	res2 = (char *)malloc(sizeof(char) * (1 + 1));
// 	fd = open("test/test1.txt", O_RDONLY);
// 	read(fd, res1, 1);
// 	read(fd, res2, 1);
// 	res1[1] = '\0';
// 	res2[1] = '\0';
// 	printf ("%s\n", res1);
// 	printf ("%s\n", res2);
// 	close(fd);
// 	return (0);
// }


// void	change_value(char **test)
// {
// 	*test = "Good morning";
// 	printf ("chenge_value's test: %s\n", *test);
// }

// int main (void)
// {
// 	char *test;

// 	test = "Hello";
// 	printf ("before executing charge_value: %s\n", test);
// 	change_value(&test);
// 	printf ("after executing charge_value: %s\n", test);

// }

// char	*test_initial(int i)
// {
// 	char *res;

// 	if (!i)
// 		return (NULL);
// 	res = "Hello";
// 	return(res);
// }

// int main(void)
// {
// 	printf ("result:%s\n", test_initial(0));
// 	// printf ("result:%s\n", test_initial(10));

// 	return (0);
// }

int main(void)
{
	char *res;

	res = "Hello\0World";
	res = 'H' + 'e' + 'l' + 'l' + 'o' + '\0' + 'W' + 'o' + 'r' + 'l' + 'd';
	printf ("res:%s\n", res);
}
