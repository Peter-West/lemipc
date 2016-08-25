#include "sdl.h"

int			find_shm_sdl(t_env_sdl *es)
{
	key_t	key;
	int		shmid;

	key = ftok("./lemipc", 'a');
	es->size = (BOARD_SIZE_X * BOARD_SIZE_Y * (sizeof(t_point))) + (sizeof(int) * 2);
	if ((shmid = shmget(key, es->size, 0666)) < 0)
	{
		perror("display shmget");
		return (-1);
	}
	if ((es->addr = shmat(shmid, NULL, 0)) == (void*)-1)
	{
		perror("display shmat");
		exit(1);
	}
	return (0);
}

void		move_player_sdl(t_env_sdl *es, int x, int y)
{
	t_coords	cds;
	SDL_Rect	rect;

	SDL_SetRenderDrawColor(es->renderer, 255, 0, 0, 255);
	cds = point_coord_in_pix(es, x, y);
	rect.x = cds.x - SQUARE_SIDE / 2;
	rect.y = cds.y - SQUARE_SIDE / 2;
	rect.w = SQUARE_SIDE;
	rect.h = SQUARE_SIDE;
	SDL_RenderFillRect(es->renderer, &rect);
}

void		read_shm_sdl(t_env_sdl *es)
{
	void	*tmp;
	t_point	*point;

	tmp = es->addr + (sizeof(int) * 2);
	while ((size_t)((void*)tmp - es->addr) < es->size)
	{
		point = (t_point*)(tmp);
		if (point->player.is_playing)
			move_player_sdl(es, point->x, point->y);
		tmp += sizeof(t_point);
	}
}