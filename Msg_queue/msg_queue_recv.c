#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "msg_queue.h"

int msg_id = -1;

int main(int argc, char *argv[])
{
    int i = 0;
    key_t key = -1;
    msg_event_t msg;
    int ret = -1;

    for (i = 0; i < MSG_QUEUE_NUM; i++)
    {
        key = ftok(KEY_DIR, 0);
        printf("%s: key[%d]: %d\n", __FUNCTION__, i, key);
    }

    msg_id = msgget(key, 0666);
    if (msg_id < 0)
    {
        printf("%s: msg get failed: %s\n", __FUNCTION__, strerror(errno));
        exit(1);
    }

    printf("%s: msg id:%d\n", __FUNCTION__, msg_id);

    while (1)
    {
        memset(&msg, 0, sizeof(msg));

        msg.msg_type = 0;

        ret = msgrcv(msg_id, &msg, sizeof(msg), 0, 0);
        if (ret < 0)
        {
            printf("%s: msg get failed: %s\n", __FUNCTION__, strerror(errno));
            exit(1);
        }
        printf("get msg: %s\n", msg.buf);
        if (0 == strcmp(msg.buf, "exit"))
        {
            printf("msg get exit\n");
            break;
        }
    }

    msgctl(msg_id, IPC_RMID, NULL);

    return 0;
}
