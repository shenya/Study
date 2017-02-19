#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_CNT 2

#define USE_SEM 0

typedef struct thread_info
{
   pthread_t tid;
   int thread_number;
} thread_info_t;

typedef struct link_node
{
    struct link_node *next;
    int number;
} link_node_t;

typedef struct manage_data
{
    link_node_t *link_list_head;
    link_node_t *link_list_tail;
    //lock
    pthread_mutex_t mutex;
    sem_t sem;
    int num;
} manage_data_t;

manage_data_t g_data;

void pthread_lock(void)
{
#ifndef USE_SEM
    pthread_mutex_lock(&g_data.mutex);
#else
    sem_wait(&g_data.sem);
#endif
}

void pthread_unlock(void)
{
#ifndef USE_SEM
    printf("%s: not use sem\n", __FUNCTION__);
    pthread_mutex_unlock(&g_data.mutex);
#else
    sem_post(&g_data.sem);
#endif
}

link_node_t *link_list_init(void)
{
    link_node_t *node = NULL;

    node = (link_node_t *)malloc(sizeof(link_node_t));
    if (NULL == node)
    {
        printf("%s: malloc failed\n", __FUNCTION__);
        return NULL;
    }
    memset(node, 0, sizeof(link_node_t));
    node->next = NULL;

    g_data.link_list_head = node;
    g_data.link_list_tail = node;    

    return node;
}

int link_list_insert_tail(link_node_t *node)
{
    if (NULL == node)
    {
        printf("%s: Invalid node\n", __FUNCTION__);
        return -1;
    }

    if (NULL == g_data.link_list_tail)
    {
        printf("%s: link list not initialized\n", __FUNCTION__);
        return -1;
    }

    node->next = NULL;
    g_data.link_list_tail->next = node;
    g_data.link_list_tail = node;

    return 0;
}

link_node_t *link_list_delete_head(void)
{
    link_node_t *node = NULL;

    if (NULL == g_data.link_list_head)
    {
        printf("%s: link list is not initialized\n", __FUNCTION__);
        return NULL;
    }

    if (NULL == g_data.link_list_head->next)
    {
        printf("%s: link list is empty\n", __FUNCTION__);
        return NULL;
    }

    node = g_data.link_list_head->next;
    g_data.link_list_head->next = node->next;
    if (NULL == node->next)
    {
        g_data.link_list_tail = g_data.link_list_head;
    }

    return node;
}

int link_list_delete_by_number(int number)
{

}

void *func(void *arg)
{
    int thread_number = 0;
    int flag = 0;

    if (NULL == arg)
    {
        printf("%s: Invalid arg\n", __FUNCTION__);
        return;
    }

    thread_number = *((int *)arg);

    while (1)
    {
        sleep(1);
        pthread_lock();
        printf("th number: %d, number: %d\n", thread_number,
                g_data.num++);
        if (g_data.num > 5)
        {
            flag = 1;
        }
        pthread_unlock();

        if (flag)
        {
            pthread_exit((void *)thread_number);
        }
    }
}

thread_info_t g_thread_info[THREAD_CNT];

int main(int argc, char *argv[])
{
    int ret = -1;
    int i = 0;
    void *exit_result = NULL;
    pthread_attr_t attr;

    pthread_mutex_init(&g_data.mutex, NULL);
    sem_init(&g_data.sem, 0, 1);

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    for (i = 0; i < THREAD_CNT; i++)
    {
        g_thread_info[i].thread_number = i;
        ret = pthread_create(&g_thread_info[i].tid, NULL, func,
                &g_thread_info[i].thread_number);
        if (0 != ret)
        {
            printf("create failed\n");
            exit(1);
        }
    }

    printf("hello world\n");
    sleep(1);
    //pthread_cancel(g_thread_info[0].tid);
    //pthread_cancel(g_thread_info[1].tid);

    ret = pthread_join(g_thread_info[0].tid, &exit_result);    
    printf("ret: %d, result: %d\n", ret, (int)exit_result);
    pthread_join(g_thread_info[1].tid, &exit_result);
    printf("result: %d\n", (int)exit_result);

    //deinit
    pthread_mutex_destroy(&g_data.mutex);
    sem_destroy(&g_data.sem);
    pthread_attr_destroy(&attr);

    return 0;
}
