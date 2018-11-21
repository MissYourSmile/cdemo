/*************************************************************************
    > File Name: ser.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月21日 星期三 22时14分56秒
 ************************************************************************/

#include "../unpipc.h"

#define SEND_MSG_TYPE 100
#define RECV_MSG_TYPE 200

int main()
{
	int msg_id = Msgget(Ftok("mymsg", 0xff), IPC_CREAT | 0775);

	struct msgbuf msg;
	while(1)	
	{
		printf("Ser.>");
		scanf("%s", msg.mtext);
		msg.mtype = SEND_MSG_TYPE;
		Msgsnd(msg_id, &msg, MSG_BUFFER_SIZE, 0);
	   	Msgrcv(msg_id, &msg, MSG_BUFFER_SIZE, RECV_MSG_TYPE, 0);
		printf("Cli.>%s\n", msg.mtext);
	}




	Msgctl(msg_id, IPC_RMID, NULL);
	return 0;
}
