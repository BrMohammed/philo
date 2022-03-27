/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:46:43 by brmohamm          #+#    #+#             */
/*   Updated: 2022/03/27 17:03:44 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PILO_H
# define PILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

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
	int *is_died;
	pthread_mutex_t m_philo_num;
	pthread_mutex_t m_print;
	pthread_mutex_t *forks;
}var_t;

int	ft_atoi(const char *str);
#endif
