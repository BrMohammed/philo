/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:46:35 by brmohamm          #+#    #+#             */
/*   Updated: 2022/03/31 16:25:29 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(t_var *my_var, int philo_number, int eating)
{
	while (*my_var->is_died != 1)
	{
		if (*my_var->philo_must_eat != -1)
		{
			if (eating == *my_var->philo_must_eat)
			{
				my_var->dieing[philo_number - 1] = -1;
				break ;
			}
		}
		eating = philosophers_continue_the_code(my_var, philo_number, eating);
		if (*my_var->is_died == 1)
			return (0);
		philo_sleep(my_var, philo_number);
		if (*my_var->is_died == 1)
			return (0);
	}
	return (0);
}

void	*philosophers(void *var)
{
	int		philo_number;
	t_var	*my_var;
	int		eating;

	my_var = (t_var *) var;
	*my_var->philo_num = *my_var->philo_num + 1;
	philo_number = *my_var->philo_num;
	eating = 0;
	philo_loop(my_var, philo_number, eating);
	return (0);
}

int	threads(pthread_t *th, t_var *var)
{
	int	i;

	if (philo_watch(var) == -1)
		return (0);
	i = 0;
	while (i++ < *var->philo_cont)
		pthread_join(th[i], NULL);
	pthread_mutex_destroy(&var->m_print);
	i = -1;
	while (++i < *var->philo_cont)
		pthread_mutex_destroy(&var->m_forks[i]);
	return (0);
}

void	parse(pthread_t *th, t_var *var)
{
	int				i;
	struct timeval	current_time;

	i = -1;
	pthread_mutex_init(&var->m_print, NULL);
	while (++i < *var->philo_cont)
		pthread_mutex_init(&var->m_forks[i], NULL);
	i = 0;
	while (i++ < *var->philo_cont)
	{
		pthread_create(&th[i], NULL, &philosophers, var);
		usleep(60);
		gettimeofday(&current_time, NULL);
		*var->utime_to_zero = current_time.tv_usec;
		*var->time_to_zero = current_time.tv_sec;
	}
}

int	main(int argc, char **argv)
{
	struct timeval		current_time;
	pthread_t			*th;
	t_var				var;

	if (argc > 4 && argc <= 6)
	{
		th = NULL;
		th = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
		var.args = creat(&var, argv, argc, &current_time);
		if (var.args == NULL)
			return (0);
		parse(th, &var);
		threads(th, &var);
	}
	else if (argc > 6)
		printf("to many args \n");
	else if (argc < 5)
		printf("few args \n");
	return (0);
}
