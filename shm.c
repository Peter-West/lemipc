#include "lemipc.h"

void	init_shm(t_env *e)
{
	e->size = (BOARD_SIZE_X * BOARD_SIZE_Y * (sizeof(t_point))) + (sizeof(int) * 2);
	
	printf("size : %zu\n", e->size);
	printf("key : %d\n", e->key);
	if ((e->shmid = shmget(e->key, e->size, IPC_CREAT | IPC_EXCL | 0666)) < 0)
	{
		perror("shmget");
		printf("e->shmid : %d\n", e->shmid);
		exit(1);
	}
	printf("e->shmid : %d\n", e->shmid);
	if ((e->addr = shmat(e->shmid, NULL, 0)) == (void*)-1)
	{
		perror("shmat");
		exit(1);
	}
	*((int*)e->addr) = 0;
	*((int*)(e->addr + sizeof(int))) = 0;
}

int		find_shm(t_env *e)
{
	e->size = (BOARD_SIZE_X * BOARD_SIZE_Y * (sizeof(t_point))) + (sizeof(int) * 2);
	if ((e->shmid = shmget(e->key, e->size, 0666)) < 0)
	{
		perror("shmget");
		return (-1);
	}
	if ((e->addr = shmat(e->shmid, NULL, 0)) == (void*)-1)
	{
		perror("shmat");
		exit(1);
	}
	return (0);
}