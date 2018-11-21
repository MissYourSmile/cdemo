/*************************************************************************
    > File Name: ser.c
    > Author: DHD
    > Mail: 1423191087@qq.com
    > Created Time: 2018年11月21日 星期三 22时14分56秒
 ************************************************************************/

#include "../unpipc.h"

#define SEND_MSG_TYPE 200
#define RECV_MSG_TYPE 100

int main()
{
	int msg_id = Msgget(Ftok("mymsg", 0xff), 0);

	struct msgbuf msg;
	while(1)	
	{
	   	Msgrcv(msg_id, &msg, MSG_BUFFER_SIZE, RECV_MSG_TYPE, 0);
		printf("Ser.>%s\n", msg.mtext);
		printf("Cli.>");
		scanf("%s", msg.mtext);
		msg.mtype = SEND_MSG_TYPE;
		Msgsnd(msg_id, &msg, MSG_BUFFER_SIZE, 0);
	}
	return 0;
}
