#ifndef __MSG_QUEUE_H__
#define __MSG_QUEUE_H__

#define KEY_DIR "/tmp"
#define MSG_QUEUE_NUM 1

typedef struct msg_event_s
{
    long int msg_type;

    char buf[512];
} msg_event_t;

#endif
