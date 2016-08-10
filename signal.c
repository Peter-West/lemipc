#include "lemipc.h"

t_env *s;

void	catch_sig(int sig)
{
	printf("\nsignal caught : %d\n", sig);
	clear_shm(s);
	clear_sem(s);
	clear_msgq(s);
	exit(1);
}

void	signal_handling(t_env *e)
{
	s = e;
	if (signal(SIGINT, catch_sig) < 0)
	{
		perror("signal");
		exit(1);
	}
}