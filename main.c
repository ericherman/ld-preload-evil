#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *str;
	int buf_size;

	buf_size = (argc > 1) ? atoi(argv[1]) : 80;

	str = malloc(buf_size);
	if (!str) {
		fprintf(stderr, "malloc failed\n");
		return EXIT_FAILURE;
	}
	strcpy(str, "bar");
	printf("foo%s\n", str);
	return EXIT_SUCCESS;
}
