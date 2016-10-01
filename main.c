/*
  Copyright (C) 2016 Eric Herman

  A test program to explore how LD_PRELOAD can be used to change behavior.

  This is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or (at
  your option) any later version.
*/

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
