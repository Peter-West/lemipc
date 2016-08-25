#ifndef SDL_H
# define SDL_H
# define SCREEN_WIDTH	640
# define SCREEN_HEIGHT	480
# define MIN			50.0
# define MAX			400.0
# define SQUARE_SIDE	20
# include "lemipc.h"
# include <SDL2/SDL.h>

typedef struct		s_coords
{
	double			x;
	double			y;
}					t_coords;

typedef struct		s_env_sdl
{
	SDL_Window		*win;
	SDL_Surface		*scr_surf;
	SDL_Renderer	*renderer;
	void			*addr;
	size_t				size;
	// key_t			key;
	double			board_x[BOARD_SIZE_X];
	double			board_y[BOARD_SIZE_Y];
}					t_env_sdl;

void		create_renderer(t_env_sdl *es);
void		print_board_vertical(t_env_sdl *es);
void		print_board_horizontal(t_env_sdl *es);
void		display(t_env_sdl *es);
void		create_window(t_env_sdl *es);
void		destroy_window(t_env_sdl *es);
t_coords	point_coord_in_pix(t_env_sdl *es, int x, int y);
void		read_shm_sdl(t_env_sdl *es);
int			find_shm_sdl(t_env_sdl *es);

#endif