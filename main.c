/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:46:35 by brmohamm          #+#    #+#             */
/*   Updated: 2022/03/27 20:38:16 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(t_var *my_var, int philo_number, int eating)
{
	while (*my_var->is_died != 1)
	{
		if (*my_var->philo_must_eat)
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
	pthread_mutex_lock (&my_var->m_philo_num);
	*my_var->philo_num = *my_var->philo_num + 1;
	philo_number = *my_var->philo_num;
	pthread_mutex_unlock (&my_var->m_philo_num);
	eating = 0;
	philo_loop(my_var, philo_number, eating);
	return (0);
}

void	threads(pthread_t *th, pthread_t wth, t_var *var)
{
	int	i;

	i = 0;
	while (i++ < *var->philo_cont)
		pthread_join(th[i], NULL);
	pthread_detach(wth);
	pthread_mutex_destroy(&var->m_philo_num);
	pthread_mutex_destroy(&var->m_print);
	i = -1;
	while (++i < *var->philo_cont)
		pthread_mutex_destroy(&var->forks[i]);
}

void	parse(pthread_t *th, pthread_t wth, t_var *var)
{
	int	i;

	i = -1;
	pthread_mutex_init(&var->m_philo_num, NULL);
	pthread_mutex_init(&var->m_print, NULL);
	while (++i < *var->philo_cont)
		pthread_mutex_init(&var->forks[i], NULL);
	i = 0;
	pthread_create(&wth, NULL, &philo_watch, var);
	while (i++ < *var->philo_cont)
	{
		pthread_create(&th[i], NULL, &philosophers, var);
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	struct timeval		current_time;
	pthread_t			*th;
	pthread_t			wth;
	t_var				var;

	if (argc > 4 && argc <= 6)
	{
		wth = NULL;
		th = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
		var.args = creat(&var, argv, argc, &current_time);
		parse(th, wth, &var);
		threads(th, wth, &var);
	}
	else if (argc > 6)
		printf("to many args \n");
	return (0);
}
