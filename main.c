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

void	mng_player(t_env *e, char *team)
{
	printf("Team : %s\n", team);
	*((int*)e->addr) += 1;
	if (!check_team_nbr(team))
		exit(1);
	e->team = (ft_atoi(team));
	e->player = getpid();
	e->num = *((int*)e->addr);
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

int main(int argc, char **argv)
{
	t_env	e;

	e.key = ftok(argv[0], 'a');
	printf("key : %d\n", e.key);
	srand(time(NULL));
	if (argc < 2)
	{
		signal_handling(&e);
		init_shm(&e);
		init_sem(&e);
		init_msgq(&e);
		create_board(&e);
		while (1)
		{
			test_print(&e);
			// msg_read(&e);
			sleep(1);
		}
	}
	else if (argc == 2)
	{
		find_shm(&e);
		find_sem(&e);
		find_msgq(&e);
		mng_player(&e, argv[1]);
		starting_point(&e);
		while (1)
		{
			op_sem_proberen(&e);
			test_print(&e);
			if (check_elim(&e))
				player_lost(&e);
			begin_turn(&e);
			// msg_send(&e);
			op_sem_verhogen(&e);
			sleep(2);
		}
	}
	else
		printf("Usage : %s [team]\n", argv[0]);
	return (0);
}