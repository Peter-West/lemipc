#include "lemipc.h"

void	test_play(t_env *e)
{
	t_point	*p;	
	void	*ret;

	p = (t_point*)(e->curr_ptr);
	if (e->leader == 1 && (ret = check_dir(e, looking_for_nearest_foe(e))))
	{
		swap_info(e->curr_ptr, ret);
		e->curr_ptr = ret;
	}
	else if ((ret = check_dir(e, find_target(e))))
	{
		swap_info(e->curr_ptr, ret);
		if (ret)
			e->curr_ptr = ret;
	}
}

char	find_target(t_env *e)
{
	t_point	*point;
	void	*tmp;
	char	c;

	tmp = e->addr + (sizeof(int) * 2);
	while ((size_t)((void*)tmp - e->addr) < e->size)
	{
		point = (t_point*)(tmp);
		if (point->player.player > 0 && point->player.player == e->target)
		{
			c = follow_foe(e,point);
			return (c);
		}
		tmp += sizeof(t_point);
	}
	return ('s');
}


char	egal_dist(t_env *e, int x, int y, t_point *curr)
{
	printf("**egal distance !\n");
	if (x > 0 && is_point_occupied(e, curr->x + 1, curr->y))
		return ('r');
	else if (x < 0 && is_point_occupied(e, curr->x - 1, curr->y))
		return ('l');
	else if (y > 0 && is_point_occupied(e, curr->x, curr->y + 1))
		return ('d');
	else if (y < 0 && is_point_occupied(e, curr->x, curr->y - 1))
		return ('u');
	else
		return ('s');
}

char	follow_foe(t_env *e, t_point *nearest)
{
	t_point *curr_pt;
	int		x;
	int		y;

	if (!nearest)
		return ('s');
	curr_pt = (t_point*)(e->curr_ptr);
	x = nearest->x - curr_pt->x;
	y = nearest->y - curr_pt->y;
	// printf("dist nearest x : %d\n", x);
	// printf("dist nearest y : %d\n", y);
	if (abs(x) > abs(y))
	{
		if (x > 0)
			return ('r');
		else
			return ('l');
	}
	else if (abs(x) < abs(y))
	{
		if (y > 0)
			return ('d');
		else
			return ('u');
	}
	else
		return (egal_dist(e, x, y, curr_pt));
}

char	looking_for_nearest_foe(t_env *e)
{
	void	*tmp;
	t_point *point;
	t_point *curr_pt;
	t_point	*nearest;
	int		res;

	res = BOARD_SIZE_X + BOARD_SIZE_Y;
	curr_pt = (t_point*)(e->curr_ptr);
	tmp = e->addr + (sizeof(int) * 2);
	nearest = NULL;
	while ((size_t)((void*)tmp - e->addr) < e->size)
	{
		point = ((t_point*)(tmp));
		if (res > abs(point->x - curr_pt->x) + abs(point->y - curr_pt->y) &&
			(point->player.team != curr_pt->player.team) &&
			point->player.is_playing == 1)
		{
			res = abs(point->x - curr_pt->x) + abs(point->y - curr_pt->y);
			nearest = point;
		}
		tmp += sizeof(t_point);
	}
	// printf("nearest : %p\n", nearest);
	if (nearest)
		msg_send(e, nearest->player.player);
	char c = follow_foe(e, nearest);
	// printf("char selected : %c\n", c);
	return (c);
}
