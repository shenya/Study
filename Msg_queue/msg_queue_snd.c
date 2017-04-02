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

int msg_queue_limit_test()
{
    struct msqid_ds msq_ds;
    int ret = -1;
    int i = 0;
    int limit = 80;
    char buf[512] = "hello";
    msg_event_t msg;

    memset(&msq_ds, 0, sizeof(msq_ds));
    ret = msgctl(msg_id, IPC_STAT, &msq_ds);
    if (ret < 0)
    {
        printf("%s: msg get failed: %s\n", __FUNCTION__, strerror(errno));
        exit(1);
    }

    printf("msg_stime: %ld, msg_rtime: %ld, msg_ctime: %ld, msg_qnum: %ld,"
            "msg_qbytes:%ld\n",
            msq_ds.msg_stime, msq_ds.msg_rtime, msq_ds.msg_ctime, msq_ds.msg_qnum,
            msq_ds.msg_qbytes);

    memset(&msq_ds, 0, sizeof(msq_ds));
    msq_ds.msg_qbytes = 16384 * 2;

    ret = msgctl(msg_id, IPC_SET, &msq_ds);
    if (ret < 0)
    {
        printf("%s: msg set failed: %s\n", __FUNCTION__, strerror(errno));
        exit(1);
    }

    ret = msgctl(msg_id, IPC_STAT, &msq_ds);
    if (ret < 0)
    {
        printf("%s: msg get failed: %s\n", __FUNCTION__, strerror(errno));
        exit(1);
    }

    printf("2:msg_stime: %ld, msg_rtime: %ld, msg_ctime: %ld, msg_qnum: %ld,"
        "msg_qbytes:%ld\n",
        msq_ds.msg_stime, msq_ds.msg_rtime, msq_ds.msg_ctime, msq_ds.msg_qnum,
        msq_ds.msg_qbytes);

    msg.msg_type = 1;
    strcpy(msg.buf, buf);
    for (i = 0; i < limit; i++)
    {
        printf("i: %d\n", i);
        ret = msgsnd(msg_id, &msg, sizeof(msg) - sizeof(long int), IPC_NOWAIT);
        if (ret < 0)
        {
            printf("%s: msg send failed: %s\n", __FUNCTION__, strerror(errno));
            exit(1);
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int i = 0;
    key_t key = -1;
    char buf[32] = {0};
    msg_event_t msg;
    int ret = -1;
    struct msqid_ds msq_ds;

    for (i = 0; i < MSG_QUEUE_NUM; i++)
    {
        key = ftok(KEY_DIR, 0);
        printf("%s: key[%d]: %d\n", __FUNCTION__, i, key);
    }

    msg_id = msgget(key, IPC_CREAT | 0666);
    if (msg_id < 0)
    {
        printf("%s: msg get failed: %s\n", __FUNCTION__, strerror(errno));
        exit(1);
    }

    printf("%s: msg id:%d\n", __FUNCTION__, msg_id);

    memset(&msq_ds, 0, sizeof(msq_ds));
    ret = msgctl(msg_id, IPC_STAT, &msq_ds);
    if (ret < 0)
    {
        printf("%s: msg get failed: %s\n", __FUNCTION__, strerror(errno));
        exit(1);
    }

    printf("msg_stime: %ld, msg_rtime: %ld, msg_ctime: %ld, msg_qnum: %ld,"
            "msg_qbytes:%ld\n",
            msq_ds.msg_stime, msq_ds.msg_rtime, msq_ds.msg_ctime, msq_ds.msg_qnum,
            msq_ds.msg_qbytes);

    //msg_queue_limit_test();

    while (1)
    {
        memset(&msg, 0, sizeof(msg));
        ret = read(STDIN_FILENO, buf, sizeof(buf));
        if (ret <= 0)
        {
            printf("%s: read from stdin %s\n", __FUNCTION__, strerror(errno));
            break;
        }

        buf[ret - 1] = '\0';

        msg.msg_type = 1;
        strcpy(msg.buf, buf);
        ret = msgsnd(msg_id, &msg, sizeof(msg) - sizeof(long int), IPC_NOWAIT);
        if (ret < 0)
        {
            printf("%s: msg send failed: %s\n", __FUNCTION__, strerror(errno));
            exit(1);
        }

        if (0 == strcmp(buf, "exit"))
        {
            printf("msg snd exit\n");
            break;
        }
    } 

    return 0;
}
