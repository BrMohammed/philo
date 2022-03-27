/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:42:30 by brmohamm          #+#    #+#             */
/*   Updated: 2022/03/27 20:12:58 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	table_of_forks_and_dieing(t_var *var)
{
	int	i;
	int	number_of_forks;

	number_of_forks = var->args[0];
	var->forks = malloc(number_of_forks * sizeof(pthread_mutex_t));
	var->dieing = malloc(number_of_forks * sizeof(int));
	i = 0;
	while (i < number_of_forks)
	{
		var->dieing[i] = 0;
		i++;
	}
}

void	allocation(t_var *var)
{
	var->is_died = malloc(sizeof(int));
	var->time_to_die = malloc(sizeof(int));
	var->time_to_eat = malloc(sizeof(int));
	var->time_to_sleep = malloc(sizeof(int));
	var->utime_to_zero = malloc(sizeof(long));
	var->philo_cont = malloc(sizeof(int));
	var->time_to_zero = malloc(sizeof(long));
	var->philo_num = malloc(sizeof(int));
	var->philo_must_eat = malloc(sizeof(int));
}

int	*creat(t_var *var, char **argv, int argc,
					struct timeval *current_time)
{
	int	i;

	i = 0;
	var->args = malloc(argc * sizeof(int));
	var->args[argc] = '\0';
	while (argv[++i])
		var->args[i - 1] = ft_atoi(argv[i]);
	allocation(var);
	*var->time_to_die = var->args[1] * 1000;
	*var->time_to_eat = var->args[2] ;
	*var->time_to_sleep = var->args[3];
	if (var->args[4])
		*var->philo_must_eat = var->args[4];
	table_of_forks_and_dieing(var);
	var->philo_cont = &var->args[0];
	gettimeofday(current_time, NULL);
	*var->utime_to_zero = current_time->tv_usec;
	*var->time_to_zero = current_time->tv_sec;
	return (var->args);
}

int	gettime(t_var *my_var)
{
	int				time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = ((current_time.tv_sec - *my_var->time_to_zero) * 1000)
		+ ((current_time.tv_usec - *my_var->utime_to_zero) / 1000);
	return (time);
}

void	print_msg(char *word, t_var *my_var, int philo_number)
{
	pthread_mutex_lock (&my_var->m_print);
	printf("%d %d %s \n", gettime(my_var), philo_number, word);
	pthread_mutex_unlock (&my_var->m_print);
}
