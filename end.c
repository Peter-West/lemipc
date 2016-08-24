#include "lemipc.h"

void	player_lost(t_env *e)
{
	t_point	*data;

	data = e->curr_ptr;
	data->player.team = 0;
	data->player.num = 0;
	data->player.player = 0;
	data->player.is_playing = 0;
	data->player.is_leader = 0;
	printf("Player : %d from team : %d Lost !\n", e->player, e->team);
	op_sem_verhogen(e);
	exit(0);
}

void	leader_is_last(t_env *e)
{
	void	*tmp;
	t_point	*point;
	int		count;

	count = 0;
	tmp = e->addr + (sizeof(int) * 2);
	while ((size_t)((void*)tmp - e->addr) < e->size)		
	{
		point = (t_point*)(tmp);
		if (point->player.player && point->player.player != e->player)
			count++;
		tmp += sizeof(t_point);
	}
	printf("count VICTORY !! : %d\n", count);
	if (!count)
	{
		// op_sem_verhogen(e);
		clear_shm(e);
		clear_sem(e);
		clear_msgq(e);
		exit(0);
	}
}


void	kill_player(t_env *e)
{
	t_point	*data;

	data = e->curr_ptr;
	if (data->player.is_leader != 1)
	{
		data->player.team = 0;
		data->player.num = 0;
		data->player.player = 0;
		data->player.is_playing = 0;
		data->player.is_leader = 0;		
		op_sem_verhogen(e);
		exit(0);
	}
	else if (data->player.is_leader == 1)
		leader_is_last(e);
}