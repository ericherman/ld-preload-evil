#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
/* int main(int argc, char *argv[]) */
int main(void)
{
	char *foo;
	uid_t uid = getuid();

	printf("my uid: %lu\n", (unsigned long)uid);
	foo = malloc(10);
	return (foo != NULL) ? EXIT_SUCCESS : EXIT_FAILURE;
}
