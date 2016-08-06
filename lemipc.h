#ifndef LEMIPC_H
# define LEMIPC_H

# define BOARD_SIZE_X	10
# define BOARD_SIZE_Y	5
# define MAX_PLAYER		50
# define MAX_TEAM		10
# include "libft.h"
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/shm.h>
# include <sys/mman.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <signal.h>
# include <sys/sem.h>
# include <sys/msg.h>

typedef struct		s_msg{
	long mtype;
	char mtext[20];
}					t_msg;

union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
	                           (Linux-specific) */
};

typedef struct		s_player
{
	int				team;
	pid_t			player;
	int				is_playing;
	int				num;
}					t_player;

typedef struct		s_point
{
	int				x;
	int				y;
	t_player		player;
}					t_point;


typedef struct		s_env
{
	void			*addr;
	int				shmid;
	int				semid;
	int				msgqid;
	size_t			size;
	key_t			key;
	int				team;
	int				num;
	pid_t			player;
	void			*curr_ptr;
}					t_env;

void	clear_shm(t_env *e);
void	clear_sem(t_env *e);
void	clear_msgq(t_env *e);
void	swap_info(t_point *old_p, t_point *new_p);
void	*is_point_occupied(t_env *e, int x, int y);
void	*check_dir(t_env *e, char dir);
void	begin_turn(t_env *e);
void	init_sem(t_env *e);
void	find_sem(t_env *e);
void	op_sem_verhogen(t_env *e);
void	op_sem_proberen(t_env *e);
void	init_shm(t_env *e);
void	find_shm(t_env *e);
void	init_msgq(t_env *e);
void	find_msgq(t_env *e);
void	msg_read(t_env *e);
void	msg_send(t_env *e);
void	catch_sig(int sig);
void	signal_handling(t_env *e);
void	test_play(t_env *e);
char	looking_for_nearest_foe(t_env *e);
int		check_elim(t_env *e);
void	player_lost(t_env *e);


#endif