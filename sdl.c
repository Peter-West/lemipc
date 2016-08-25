#include "sdl.h"

void	create_renderer(t_env_sdl *es)
{
	es->renderer = SDL_CreateRenderer(es->win, -1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (es->renderer == NULL)
		printf("Renderer could not be created ! SDL_Error : %s\n", SDL_GetError());
}

void	move_test(t_env_sdl *es)
{
	t_coords	cds;
	SDL_Rect	rect;
	static int			i = 0;
	static int			j = 0;


	if (i == BOARD_SIZE_X)
	{
		j++;
		i = 0;
	}
	// if (j == BOARD_SIZE_Y )
		// return ;
	cds = point_coord_in_pix(es, i, j);
	rect.x = cds.x - SQUARE_SIDE / 2;
	rect.y = cds.y - SQUARE_SIDE / 2;
	rect.w = SQUARE_SIDE;
	rect.h = SQUARE_SIDE;		
	SDL_RenderFillRect(es->renderer, &rect);
	i++;
}

void	test_div(t_env_sdl *es)
{
	
	Uint8 r,g,b,a;
	r = 255;
	g = 0;
	b = 0;
	a = 255;
	SDL_SetRenderDrawColor(es->renderer, r, g, b, a);
	move_test(es);

	
}

t_coords	point_coord_in_pix(t_env_sdl *es, int x, int y)
{
	t_coords	coords;
	int			i;

	i = 0;
	while (i < x)
		i++;
	coords.x = es->board_x[i];
	i = 0;
	while (i < y)
		i++;
	coords.y = es->board_y[i];
	return (coords);
}

void	fill_board_vertical(t_env_sdl *es)
{
	int				i;
	double			x;

	i = 0;
	x = MIN;
	while (i < BOARD_SIZE_X)
	{
		printf("X : %f\n", x);
		es->board_x[i] = x;
		x += (MAX - MIN) / (BOARD_SIZE_X - 1);
		i++;
	}
}


void	fill_board_horizontal(t_env_sdl *es)
{
	int				i;
	double			y;

	i = 0;
	y = MIN;
	while (i < BOARD_SIZE_Y)
	{
		printf("Y : %f\n", y);
		es->board_y[i] = y;
		y += (MAX - MIN) / (BOARD_SIZE_Y - 1);
		i++;
	}
}

void	print_board_vertical(t_env_sdl *es)
{
	int				i;

	i = 0;
	while (i < BOARD_SIZE_X)
	{
		SDL_RenderDrawLine(es->renderer, es->board_x[i], MIN, es->board_x[i], MAX);
		i++;
	}
}

void	print_board_horizontal(t_env_sdl *es)
{
	int				i;

	i = 0;
	while (i < BOARD_SIZE_Y)
	{
		SDL_RenderDrawLine(es->renderer, MIN, es->board_y[i], MAX, es->board_y[i]);
		i++;
	}
}

void	display(t_env_sdl *es)
{
	SDL_Event	event;
	int			running;

	running = 1;
	while (running)
	{
		SDL_PollEvent (&event);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			running = 0;
			break ;
		}
		SDL_RenderClear(es->renderer);
		SDL_SetRenderDrawColor(es->renderer, 255, 255, 0, 255);
		print_board_vertical(es);
		print_board_horizontal(es);
		// test_div(es);
		read_shm_sdl(es);
		SDL_RenderPresent(es->renderer);
		SDL_SetRenderDrawColor(es->renderer, 0, 0, 0, 255);
	}
}

void	create_window(t_env_sdl *es)
{
	es->win = NULL;
	es->renderer = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	else
	{
		es->win = SDL_CreateWindow("Yop Yop, c'est la SDL 2 !", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
		if (es->win == NULL)
			 printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		else
		{
			create_renderer(es);
			display(es);            
		}
	}
}

void	destroy_window(t_env_sdl *es)
{
	//Destroy window
    SDL_DestroyWindow(es->win);
    //Destroy renderer
    SDL_DestroyRenderer(es->renderer); 
    //Quit SDL subsystems
    SDL_Quit();
}

int		main(void)
{
	t_env_sdl	es;
	
	fill_board_vertical(&es);
	fill_board_horizontal(&es);
	find_shm_sdl(&es);
	create_window(&es);

	destroy_window(&es);
	return (0);
}