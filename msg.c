#include "lemipc.h"

void	init_msgq(t_env *e)
{
	struct msqid_ds buf;

	if ((e->msgqid = msgget(e->key, (IPC_CREAT | IPC_EXCL | 0644))) == -1)
	{
		perror("msgget init");
		exit(1);
	}
	if (msgctl(e->msgqid, IPC_STAT, &buf) == -1)
	{
		perror("msgctl IPC_STAT");
		exit(1);
	}
	printf("time : %ld\n", buf.msg_ctime);
}

void	find_msgq(t_env *e)
{
	if ((e->msgqid = msgget(e->key, 0)) == -1)
	{
		perror("msgget find");
		exit(1);
	}
}

void	msg_read(t_env *e)
{
	t_msg		msgp;

	msgp.mtype = e->team;
	if (msgrcv(e->msgqid, &msgp, sizeof(msgp) - sizeof(long), e->team,
		 IPC_NOWAIT ) == -1)
		perror("msgrcv");
	else
	{
		e->target = msgp.target;
		printf("msg rcv, team : %d, target PID : %d\n", msgp.team, msgp.target);
	}
	printf("msg type : %ld\n", msgp.mtype);

}

void	msg_send(t_env *e, pid_t target)
{
	t_msg		msgp;

	msgp.mtype = e->team;
	msgp.team = e->team;
	msgp.target = target;
	printf("message to send, team : %d, target PID : %d, size %zu, type : %ld\n",
		msgp.team, msgp.target, sizeof(msgp) - sizeof(long), msgp.mtype);

	if (msgsnd(e->msgqid, &msgp, sizeof(msgp) - sizeof(long), IPC_NOWAIT) == -1)
	{
		perror("msgsnd");
		exit(1);
	}
	else
		printf("msg send !\n");
}