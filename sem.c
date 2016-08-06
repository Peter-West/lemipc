#include "lemipc.h"

void	init_sem(t_env *e)
{
	// struct sembuf	sops;
	// union semun			semts;
	// struct semid_ds		mysemds;

	if ((e->semid = semget(e->key, 1, IPC_CREAT | 0666)) < 0)
	{
		perror("semget init");
		exit(1);
	}
	printf("semid : %d\n", e->semid);

	if (semctl(e->semid, 0, SETVAL, 1) == -1)
	{
		perror("semctl setval");
		exit(1);
	}
/*	
	semts.buf = &mysemds;
	if (semctl(e->semid, 0, IPC_STAT, semts) == -1)
	{
		perror("semctl ipcstat");
		exit(1);
	}
	printf("semts.sem_nsems : %ld\n", semts.buf->sem_nsems);*/
}

void	find_sem(t_env *e)
{
	if ((e->semid = semget(e->key, 0, 0)) < 0)
	{
		perror("semget find");
		exit(1);
	}
	printf("e->semid find : %d\n", e->semid);
}

void	op_sem_proberen(t_env *e)
{
	struct sembuf		buf;
	// union semun			semts;
	// struct semid_ds		mysemds;
	int					val;

	if ((val = semctl(e->semid, 0, GETVAL)) < 0)
	{
		perror("semctl");
	}
	printf("getval : %d\n", val);
	buf.sem_num = 0;
	buf.sem_op = -1;
	buf.sem_flg = 0;
	if (semop(e->semid, &buf, 1) < 0)
	{
		perror("semop op");
		exit(1);
	}
	if ((val = semctl(e->semid, 0, GETVAL)) < 0)
	{
		perror("semctl");
	}
	printf("getval : %d\n", val);
/*
	semts.buf = &mysemds;
	if (semctl(e->semid, 0, IPC_STAT, semts) == -1)
	{
		perror("semctl ipcstat");
		exit(1);
	}
	printf("semts.sem_nsems : %ld\n", semts.buf->sem_nsems);*/
}

void	op_sem_verhogen(t_env *e)
{
	struct sembuf		buf;

	buf.sem_num = 0;
	buf.sem_op = 1;
	buf.sem_flg = 0;
	if (semop(e->semid, &buf, 1) < 0)
	{
		perror("semop op");
		exit(1);
	}
}