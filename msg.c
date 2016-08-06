#include "lemipc.h"

void	init_msgq(t_env *e)
{
	struct msqid_ds buf;

	if ((e->msgqid = msgget(e->key, (IPC_CREAT | 0644))) == -1)
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

	if (msgrcv(e->msgqid, &msgp, sizeof(msgp.mtext), 0,
		MSG_NOERROR ) == -1)
	{
		perror("msgrcv");
		// exit(1);
	}
	else
		printf("msg : %s\n", msgp.mtext);
}

void	msg_send(t_env *e)
{
	t_msg		msgp;
	int			i = 0;
	char		*tmp;

	tmp = "YOOOOO\n";
	while (i < 20)
	{
		msgp.mtext[i] = tmp[i];
		i++;
	}
	printf("msgp.mtext : %s\n", msgp.mtext);

	if (msgsnd(e->msgqid, &msgp, sizeof(msgp.mtext), IPC_NOWAIT) == -1)
	{
		perror("msgsnd");
		exit(1);
	}
	else
		printf("msg send !\n");
}