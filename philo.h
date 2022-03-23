#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct var_s
{
    int *args;
    int *forks;
    long *utime_to_zero;
    long *time_to_zero;
}var_t;
