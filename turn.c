#include "lemipc.h"

void	begin_turn(t_env *e)
{
	void	*tmp;
	t_point	*point;

	tmp = e->addr + (sizeof(int) * 2);
	while ((size_t)((void*)tmp - e->addr) < e->size)
	{
		point = ((t_point*)(tmp));
		if (point->player.player == e->player)
		{
			e->curr_ptr = point;
			if (e->leader != 1)
				check_leader(e);
			test_play(e);
			break ;
		}
		tmp += sizeof(t_point);
	}
}

int		ret_team(t_env *e, int x, int y)
{
	void	*tmp;
	t_point	*point;

	tmp = e->addr + (sizeof(int) * 2);
	while ((size_t)((void*)tmp - e->addr) < e->size)
	{
		point = ((t_point*)(tmp));
		if (point->x == x && point->y == y)
		{
			if (point->player.team > 0)
				return (point->player.team);
		}
		tmp += sizeof(t_point);
	}
	return (-1);
}

int		check_team(int up, int down, int right, int left)
{
	if (up > 0 && (up == down || up == right || up == left))
		return(1);
	else if (down > 0 && (down == right || down == left))
		return(1);
	else if (left > 0 && (left == right))
		return(1);
	else
		return (0);
}

int		check_elim(t_env *e)
{
	int		up;
	int		down;
	int		right;
	int		left;
	t_point	*point;

	up = -1;
	down = -1;
	right = -1;
	left = -1;
	point = (t_point*)(e->curr_ptr);
	if (!point)
		return (0);
	if (point->y - 1 >= 0)
		up = ret_team(e, point->x, point->y - 1);
	if (point->y + 1 <= BOARD_SIZE_Y)
		down = ret_team(e, point->x, point->y + 1);
	if (point->x + 1 <= BOARD_SIZE_X)
		right = ret_team(e, point->x + 1, point->y);
	if (point->x - 1 >= 0)
		left = ret_team(e, point->x - 1, point->y);
	if (check_team(up, down, right, left))
		return (1);
	return (0);
}

int		check_victory(t_env *e)
{
	t_point	*point;
	void	*tmp;
	int		count;

	count = 0;
	tmp = e->addr + (sizeof(int) * 2);
	while ((size_t)((void*)tmp - e->addr) < e->size)
	{
		point = (t_point*)(tmp);
		if (point->player.team != 0 && point->player.team != e->team)
			count++;
		tmp += sizeof(t_point);
	}
	printf("count check victory : %d\n", count);
	if (count > 0)
		return (0);
	return (1);
}
