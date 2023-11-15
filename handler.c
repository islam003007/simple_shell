#include "main.h"

void INThandler(int sig, char *buf)
{
	signal(sig, SIG_IGN);

	free(buf);
	exit(0);

}
