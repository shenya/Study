#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define WATCH_NUMBER 5
#define CRASH_TIMES 10
#define WATCH_TIMEOUT 30

typedef struct watch_list_s
{
    int used_flag;
    int ignore_flag;
    int crash_times;
    char program_name[16];
    int (*cb)();
} watch_list_t;

watch_list_t g_watch_list[WATCH_NUMBER];

int kamailio_cb()
{
    char cmd_buf[128] = {0};

    snprintf(cmd_buf, sizeof(cmd_buf), "kamctl start");

    system(cmd_buf);
}

void watch_dog_init(void)
{
    g_watch_list[0].used_flag = 1;
    strcpy(g_watch_list[0].program_name, "kamailio");
    g_watch_list[0].cb = kamailio_cb;
}

void watch_dog_start()
{
    int i = 0;
    char cmd_buf[32] = {0};

    sleep(3);

    while (1)
    {
        for (i = 0; i < WATCH_NUMBER; i++)
        {
            char buf[256] = {0};
            FILE *ptr = NULL;

            if (0 == g_watch_list[i].used_flag ||
                1 == g_watch_list[i].ignore_flag)
            {
                continue;
            }

            snprintf(cmd_buf, sizeof(cmd_buf), "pidof %s",
                    g_watch_list[i].program_name);
            printf("cmd buf: %s\n", cmd_buf);

            if ((ptr = popen(cmd_buf, "r")) != NULL)
            {
                while (fgets(buf, 256, ptr) != NULL)
                {
                    ;
                }
                pclose(ptr);
                ptr = NULL;
            }
            else
            {
                printf("%s: popen error\n", __FUNCTION__);
            }

            printf("buf: %s\n", buf);
            if (0 == strlen(buf))
            {
                printf("%s: progarm is not started\n", __FUNCTION__);
                if (g_watch_list[i].cb)
                {
                    g_watch_list[i].cb();
                }
                g_watch_list[i].crash_times++;

                if (CRASH_TIMES <= g_watch_list[i].crash_times)
                {
                    g_watch_list[i].ignore_flag = 1;
                }
            }
        }

        sleep(WATCH_TIMEOUT);
    }


}

int main(int argc, char *argv[])
{
    watch_dog_init();

    watch_dog_start();

    printf("hello world\n");

    return 0;
}
