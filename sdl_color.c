#include "sdl.h"

t_color		*check_already_exist(t_color *color, int team)
{
	t_color		*tmp;

	tmp = color;
	while (tmp)
	{
		if (tmp->team == team)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_color		*rand_color(int team)
{
	t_color		*new_b;
	
	new_b = (t_color*)malloc(sizeof(t_color));
	new_b->r = rand() % 255;
	new_b->g = rand() % 255;
	new_b->b = rand() % 255;
	new_b->team = team;
	return (new_b);
}

void		add_team_color(t_color **color, t_color *new_b)
{
	t_color		*tmp;

	new_b->next = NULL;
	if (!(*color))
		*color = new_b;
	else
	{
		tmp = *color;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_b;
	}
}

void		team_color(t_env_sdl *es, int team)
{
	t_color	*tmp;

	if (!(tmp = check_already_exist(es->color, team)))
	{
		tmp = rand_color(team);
		add_team_color(&(es->color), tmp);				
	}
	SDL_SetRenderDrawColor(es->renderer, tmp->r, tmp->g, tmp->b, 255);
}