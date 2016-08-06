#include "lemipc.h"

void	clear_shm(t_env *e)
{
	if (shmctl(e->shmid, IPC_RMID, 0) < 0)
	{
		perror("shmctl IPC_RMID");
		exit(1);
	}
}

void	clear_sem(t_env *e)
{
	if (semctl(e->semid, 0, IPC_RMID) < 0)
	{
		perror("semctl IPC_RMID");
		exit(1);
	}
}

void	clear_msgq(t_env *e)
{
	if (msgctl(e->msgqid, IPC_RMID, 0) == -1)
	{
		perror("msgctl IPC_RMID");
		exit(1);
	}
}

