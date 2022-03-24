#ifndef PILO_H
# define PILO_H

# include <stdio.h>
# include <stdlib.h>
# include<string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct var_s
{
    int *time_to_die;
    int* time_to_eat;
    int* time_to_sleep;

    int *args;
    int *forks;
    long *utime_to_zero;
    long *time_to_zero;
    int *philo_num;
    int *philo_cont;
    pthread_mutex_t m_philo_num;
    pthread_mutex_t m_can_eat;
}var_t;

int	ft_atoi(const char *str);
#endif
