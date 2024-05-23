#include "loadables.h"
#include "bashansi.h"
#include <config.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#ifndef SECRET_VALUE
#define SECRET_VALUE "asdf"
#endif

int challenge_builtin(WORD_LIST *list)
{
	if (!list)
	{
		puts("Incorrect usage! Please read the help page for the challenge builtin!");
		return EXECUTION_FAILURE;
	}

	if (!strcmp(list->word->word, "--fortune"))
	{
		system("/usr/games/fortune");
	}
	else if (!strcmp(list->word->word, "--version"))
	{
		puts("I'm exactly the version I need to be!");
	}
	else if (!strcmp(list->word->word, "--secret"))
	{
		if (!list->next)
		{
			puts("ERROR: missing argument to --secret.");
			return EXECUTION_FAILURE;
		}
		if (strcmp(list->next->word->word, SECRET_VALUE))
		{
			puts("ERROR: incorrect argument to --secret. Read the help!");
			return EXECUTION_FAILURE;
		}
		puts("Correct! Here is your flag!");
		char flag[1024] = { 0 };
		int fd = open("/flag", 0);
		read(fd, flag, 1024);
		puts(flag);
	}
  	//SHELL_VAR *pwn = find_variable("PWN");
  	//if (pwn == NULL) {
    	//	printf("NOPE\n");
    	//	return EXECUTION_SUCCESS;
  	//}
  	//printf("%s\n", get_variable_value(pwn));

  	return EXECUTION_SUCCESS;
}

int challenge_builtin_load(char *name)
{
  	//bind_global_variable("PWN", "COLLEGE", 0);
  	return (1); // 0 == fail
}

void challenge_builtin_unload(char *name)
{
}

char *challenge_doc[] = {
	"This builtin command will read you the flag, given the right arguments!"
	(
	 ""
	 "\n"
	 "\tOptions:\n"
	 "\t  --fortune		display a fortune\n"
	 "\t  --version		display the version\n"
	 "\t  --secret VALUE	prints the flag, if VALUE is correct\n"
	 "\n"
	 "\tYou must be sure to provide the right value to --secret. That value\n"
	 "\tis \"" SECRET_VALUE "\"."
	),
	(char *)NULL
};

struct builtin challenge_struct = {
	"challenge",			/* builtin name */
	challenge_builtin,		/* function implementing the builtin */
	BUILTIN_ENABLED,		/* initial flags for builtin */
	challenge_doc,			/* array of long documentation strings. */
	"challenge [--fortune] [--version] [--secret SECRET]",			/* usage synopsis; becomes short_doc */
	0				/* reserved for internal use */
};
