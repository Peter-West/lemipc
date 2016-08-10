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
