#include "lemipc.h"

void	swap_info(t_point *old_p, t_point *new_p)
{
	new_p->player = old_p->player;
	old_p->player.team = 0;
	old_p->player.player = 0;
	old_p->player.is_playing = 0;
	old_p->player.num = 0;
}

void	*is_point_occupied(t_env *e, int x, int y)
{
	void	*tmp;
	t_point	*point;

	tmp = e->addr + (sizeof(int) * 2);
	printf("is_point_occupied X : %d\n", x);
	printf("is_point_occupied Y : %d\n", y);
	while ((size_t)((void*)tmp - e->addr) < e->size)
	{
		point = (t_point*)(tmp);
		if (point->x == x && point->y == y && point->player.is_playing == 0)
			return (point);
		tmp += sizeof(t_point);
	}
	return (NULL);
}

void	*check_dir(t_env *e, char dir)
{
	t_point	*point;

	point = (t_point*)(e->curr_ptr);
	if (dir == 'u' && (point->y - 1) >= 0)
		return (is_point_occupied(e, point->x, point->y - 1));
	else if (dir == 'd' && (point->y + 1) <= BOARD_SIZE_Y)
		return (is_point_occupied(e, point->x, point->y + 1));
	else if (dir == 'r' && (point->x + 1) <= BOARD_SIZE_X)
		return (is_point_occupied(e, point->x + 1, point->y));
	else if (dir == 'l' && (point->x + 1) >= 0)
		return (is_point_occupied(e, point->x - 1, point->y));
	else
		return (NULL);
}

