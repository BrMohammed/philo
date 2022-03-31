/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:42:30 by brmohamm          #+#    #+#             */
/*   Updated: 2022/03/31 16:16:59 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	table_of_m_forks_and_dieing(t_var *var)
{
	int	i;
	int	number_of_m_forks;

	number_of_m_forks = var->args[0];
	var->m_forks = malloc(number_of_m_forks * sizeof(pthread_mutex_t));
	var->dieing = (int *)malloc(sizeof(int) * number_of_m_forks);
	i = 0;
	while (i < number_of_m_forks)
	{
		var->dieing[i] = 0;
		i++;
	}
}

int	allocation(t_var *var, char **argv, int argc)
{
	int	i;

	i = 0;
	i = 0;
	var->args = (int *)malloc(sizeof(int) * (argc - 1));
	while (argv[i + 1] && i < argc)
	{
		if (ft_isdigit(argv[i + 1]) == 1)
		{
			printf("invalid argiment\n");
			return (-1);
		}
		var->args[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	var->is_died = malloc(sizeof(int));
	var->time_to_die = malloc(sizeof(int));
	var->time_to_eat = malloc(sizeof(int));
	var->time_to_sleep = malloc(sizeof(int));
	var->utime_to_zero = malloc(sizeof(long));
	var->philo_cont = malloc(sizeof(int));
	var->time_to_zero = malloc(sizeof(long));
	var->philo_num = malloc(sizeof(int));
	var->philo_must_eat = malloc(sizeof(int));
	return (0);
}

int	*creat(t_var *var, char **argv, int argc,
					struct timeval *current_time)
{
	if (allocation(var, argv, argc) == -1)
		return (NULL);
	*var->time_to_die = var->args[1];
	*var->time_to_eat = var->args[2];
	*var->time_to_sleep = var->args[3];
	if (argv[5])
		*var->philo_must_eat = var->args[4];
	else
		*var->philo_must_eat = -1;
	table_of_m_forks_and_dieing(var);
	*var->philo_cont = var->args[0];
	gettimeofday(current_time, NULL);
	*var->utime_to_zero = current_time->tv_usec;
	*var->time_to_zero = current_time->tv_sec;
	*var->is_died = 0;
	*var->philo_num = 0;
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

int	print_msg(char *word, t_var *my_var, int philo_number)
{
	pthread_mutex_lock (&my_var->m_print);
	if (*my_var->is_died != 1)
		printf("%d %d %s \n", gettime(my_var), philo_number, word);
	pthread_mutex_unlock (&my_var->m_print);
	return (0);
}
