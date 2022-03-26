#ifndef PILO_H
# define PILO_H

# include <stdio.h>
# include <stdlib.h>
# include<string.h>
# include <pthread.h>
# include <sys/time.h>
#   include <unistd.h>

typedef struct var_s
{
    int *time_to_die;
    int* time_to_eat;
    int* time_to_sleep;
    int* philo_must_eat;
    int *dieing;
    int *args;
    long *utime_to_zero;
    long *time_to_zero;
    int *philo_num;
    int *philo_cont;
    pthread_mutex_t m_philo_num;
    pthread_mutex_t *forks;
}var_t;

int	ft_atoi(const char *str);
#endif
