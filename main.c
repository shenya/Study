#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sort_algorithm.h"

#define NUM 10

int array[NUM];

void init_array()
{
    int i;
    struct timeval tpstart;

    gettimeofday(&tpstart,NULL);
    srand(tpstart.tv_usec);

    for (i = 0; i < NUM; i++) {
        array[i] = rand() % 100 + 100;
    }
}

void show_array()
{
   int i;

   for (i = 0; i < NUM; i++) {
       printf("%5d", array[i]);
   }

   printf("\n");
}

int main(void)
{
    init_array();
    show_array();
    bubble_sort(array, NUM);
    show_array();
    printf("hello world\n");
    return 0;
}
