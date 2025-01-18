#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// void pointer_test(char **res)
// {
// 	free (*res);
// 	*res = (char *)malloc(sizeof(char) * (11 + 1));
// 	if (!(*res))
// 		return ;
// 	*res = strcpy(*res, "Hello World");
// 	printf ("in the func : %s\n", *res);
// }

// int main (void)
// {
// 	char *res;

// 	res = (char *)malloc(sizeof(char) * (5 + 1));
// 	if (!res)
// 		return (1);
// 	res = strcpy(res, "Hello");
// 	printf ("before func : %s\n", res);
// 	pointer_test (&res);
// 	printf ("after func : %s\n", res);
// }

// void modifyString(char *str) {
//     str = "World";
// 	printf ("%s\n", str);
// }

// int main() {
//     char *str = "Hello";
//     modifyString(str);
//     printf("%s\n", str);  // "Hello"が出力される
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// void allocateString(char *str, const char *value) {
//     str = (char *)malloc(strlen(value) + 1);  // メモリ確保
//     if (str != NULL) {
//         strcpy(str, value);  // 値をコピー
//     }
// }

// int main() {
//     char *str = NULL;
//     allocateString(str, "Hello, World!");
//     printf("%s\n", str);  // "Hello, World!"が出力される
//     free(str);  // メモリ解放
//     return 0;
// }
