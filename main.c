#include "lemipc.h"


void	test_print(t_env *e)
{
	int		i;
	void	*tmp;

	i = 0;
	printf("number of player : %d\n", *((int*)e->addr));
	printf("current player : %d\n", *((int*)(e->addr + sizeof(int))) );
	tmp = e->addr + (sizeof(int) * 2);
	while ( (size_t)((void*)tmp - e->addr) < e->size)
	{
		if (i % BOARD_SIZE_X == 0 && i > 0)
			printf("\n");
		printf("%d ", ((t_point*)tmp)->player.team);
		i++;
		tmp += sizeof(t_point);
	}
	printf("\n");
}

void	create_board(t_env *e)
{
	int		x;
	int		y;
	t_point	*data;
	void	*mem_ptr;

	y = 0;
	mem_ptr = e->addr + (sizeof(int) * 2);
	while (y < BOARD_SIZE_Y)
	{
		x = 0;
		while (x < BOARD_SIZE_X)
		{
			data = mem_ptr;
			data->x = x;
			data->y = y;
			data->player.team = 0;
			data->player.player = 0;
			data->player.is_leader = 0;
			data->player.is_playing = 0;
			mem_ptr += sizeof(t_point);
			x++;
		}
		y++;
	}
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
			return(0);
		}
		i++;
	}
	if (ft_atoi(team) < 1)
	{
		printf("Team must superior to zero\n");
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

void		*place_player_start(t_env *e, int x, int y)
{
	int		i;
	int		j;
	void	*tmp;
	t_point	*point;
	
	tmp = e->addr + (sizeof(int) * 2);
	i = 0;
	while (i < BOARD_SIZE_Y)
	{
		j = 0;
		while(j < BOARD_SIZE_X)
		{
			point = ((t_point*)(tmp));
			if (point->x == x && point->y == y && !point->player.is_playing)
			{
				point->player.team = e->team;
				return (point);
			}
			tmp += sizeof(t_point);
			j++;
		}
		i++;
	}
	return (NULL);
}

void	starting_point(t_env *e)
{
	int		x;
	int		y;
	void	*loop;

	srand(time(NULL));
	loop = NULL;
	while (!loop)
	{
		y = rand() % BOARD_SIZE_Y;
		x = rand() % BOARD_SIZE_X;
		loop = place_player_start(e, x, y);
	}
	((t_point*)(loop))->player.player = e->player;
	((t_point*)(loop))->player.is_playing = 1;
	((t_point*)(loop))->player.num = *((int*)e->addr);
}

void	init_env(t_env *e, char *team)
{
	signal_handling(e);
	if (find_shm(e) == -1)
	{
		init_shm(e);
		init_sem(e);
		init_msgq(e);
		create_board(e);	
	}
	else 
	{
		find_sem(e);
		find_msgq(e);
	}
	mng_player(e, team);
	starting_point(e);
}

int main(int argc, char **argv)
{
	t_env	e;

	e.key = ftok(argv[0], 'a');
	if (argc == 2)
	{
		init_env(&e, argv[1]);
		while (1)
		{
			op_sem_proberen(&e);
			test_print(&e);
			if (check_elim(&e))
				player_lost(&e);
			msg_read(&e);
			begin_turn(&e);
			op_sem_verhogen(&e);
			if (check_victory(&e))
				printf("VICTOIRRRRRRRRE team : %d\n", e.team);
			printf("leader : %d\n", e.leader);
			sleep(2);
		}
	}
	else
		printf("Usage : %s [team]\n", argv[0]);
	return (0);
}