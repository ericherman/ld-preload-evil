/*
  Copyright (C) 2016 Eric Herman

  A program to directly test the "evil" library.

  This is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or (at
  your option) any later version.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

extern size_t evil_size;

/* int main(int argc, char *argv[]) */
int main(void)
{
	char *foo;
	uid_t uid = getuid();

	printf("my uid: %lu\n", (unsigned long)uid);
	foo = malloc(evil_size);
	return (foo != NULL) ? EXIT_SUCCESS : EXIT_FAILURE;
}
