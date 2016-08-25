#include "lemipc.h"

void	check_start(t_env *e)
{
	void		*tmp;
	t_point		*point;
	int			count;
	int			same_team_player;

	same_team_player = 0;
	count = 0;
	tmp = e->addr + (sizeof(int) * 2);
	// while (!*((int*)(e->addr + sizeof(int))))
	// {
	while ( (size_t)((void*)tmp - e->addr) < e->size)		
	{
		point = (t_point*)(tmp);
		if (point->player.team == e->team)
			same_team_player++;
		if (same_team_player > 1 && point->player.team != e->team
			&& point->player.is_playing)
		{
			// printf("STARTTT *** \n");
			*((int*)(e->addr + sizeof(int))) = 1;
			return ;
		}
		tmp += sizeof(t_point);
	}
	// }
}

int		check_team_nbr(char *team)
{
	int		i;

	i = 0;
	while (team[i] != '\0')
	{
		if (!ft_isdigit(team[i]))
		{
			printf("Team must be a number\n");
			return (0);
		}
		i++;
	}
	if (ft_atoi(team) < 1)
	{
		printf("Team must superior to zero\n");
		return (0);
	}
	return (1);
}

void	check_leader(t_env *e)
{
	void		*tmp;
	t_point		*point;

	tmp = e->addr + (sizeof(int) * 2);
	while ( (size_t)((void*)tmp - e->addr) < e->size)		
	{
		point = (t_point*)(tmp);
		if (point->player.team == e->team && point->player.is_leader)
		{
			e->leader = point->player.player;
			return ;
		}
		tmp += sizeof(t_point);
	}
	((t_point*)(e->curr_ptr))->player.is_leader = 1;
	e->leader = 1;
}

void	mng_player(t_env *e, char *team)
{
	printf("Team : %s\n", team);
	*((int*)e->addr) += 1;
	if (!check_team_nbr(team))
		exit(1);
	e->team = (ft_atoi(team));
	e->player = getpid();
	e->num = *((int*)e->addr);
	e->target = 0;
}

void	init_env(t_env *e, char *team)
{
	signal_handling(e);
	if (find_shm(e) == -1)
	{
		printf("INIT !\n");
		init_shm(e);
		init_sem(e);
		init_msgq(e);
		create_board(e);	
	}
	else 
	{
		printf("FIND !\n");
		find_sem(e);
		find_msgq(e);
	}
	mng_player(e, team);
	starting_point(e);
}