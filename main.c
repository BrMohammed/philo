/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:46:35 by brmohamm          #+#    #+#             */
/*   Updated: 2022/03/28 18:52:08 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_loop(t_var *my_var, int philo_number, int eating)
{
	while (1)
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
	pthread_mutex_lock (&my_var->m_philo_num);
	*my_var->philo_num = *my_var->philo_num + 1;
	philo_number = *my_var->philo_num;
	pthread_mutex_unlock (&my_var->m_philo_num);
	eating = 0;
	philo_loop(my_var, philo_number, eating);
	return (0);
}

int	threads(pthread_t *th, t_var *var)
{
	int	i;

	i = 0;
	if (philo_watch(var) == 1)
		return (0);
	while (i++ < *var->philo_cont)
		pthread_join(th[i], NULL);
	pthread_mutex_destroy(&var->m_philo_num);
	pthread_mutex_destroy(&var->m_print);
	pthread_mutex_destroy(&var->m_death);
	i = -1;
	while (++i < *var->philo_cont)
		pthread_mutex_destroy(&var->m_forks[i]);
	return (0);
}

void	parse(pthread_t *th, t_var *var)
{
	int	i;

	i = -1;
	pthread_mutex_init(&var->m_philo_num, NULL);
	pthread_mutex_init(&var->m_print, NULL);
	pthread_mutex_init(&var->m_death, NULL);
	while (++i < *var->philo_cont)
		pthread_mutex_init(&var->m_forks[i], NULL);
	i = 0;
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
	t_var				var;

	if (argc > 4 && argc <= 6)
	{
		th = NULL;
		th = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
		if (creat(&var, argv, argc, &current_time) == NULL)
			return (0);
		var.args = creat(&var, argv, argc, &current_time);
		parse(th, &var);
		threads(th, &var);
	}
	else if (argc > 6)
		printf("to many args \n");
	else if (argc < 5)
		printf("few args \n");
	return (0);
}
