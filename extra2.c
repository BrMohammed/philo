/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:46:26 by brmohamm          #+#    #+#             */
/*   Updated: 2022/03/30 01:31:42 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers_continue_the_code(t_var *my_var, int philo_number, int eating)
{
	pthread_mutex_lock (&my_var->m_forks[philo_number -1]);
	print_msg("has taken a fork", my_var, philo_number);
	if (condetion_of_one_philo(my_var) == 1)
		return (0);
	if (philo_number == my_var->args[0])
	{
		pthread_mutex_lock (&my_var->m_forks[0]);
		print_msg("has taken a fork", my_var, philo_number);
	}
	else
	{
		pthread_mutex_lock (&my_var->m_forks[philo_number]);
		print_msg("has taken a fork", my_var, philo_number);
	}
	my_var->dieing[philo_number - 1] = gettime(my_var);
	philo_eat(my_var, philo_number);
	eating++;
	pthread_mutex_unlock (&my_var->m_forks[philo_number -1]);
	if (philo_number == my_var->args[0])
		pthread_mutex_unlock (&my_var->m_forks[0]);
	else
		pthread_mutex_unlock (&my_var->m_forks[philo_number]);
	return (eating);
}

void	*philo_eat(t_var *my_var, int philo_number)
{
	int	i;

	if (*my_var->is_died == 1)
	{
		usleep(10);
		return (0);
	}
	print_msg("is eating", my_var, philo_number);
	i = gettime(my_var);
	while (gettime(my_var) - i < (*my_var->time_to_eat))
		usleep(1000);
	return (0);
}

void	*philo_sleep(t_var *my_var, int philo_number)
{
	int	i;

	if (*my_var->is_died == 1)
		return (0);
	print_msg("is slepping", my_var, philo_number);
	i = gettime(my_var);
	while (gettime(my_var) - i <= *my_var->time_to_sleep)
		usleep(1000);
	if (*my_var->is_died == 1)
		return (0);
	print_msg("is thinking", my_var, philo_number);
	return (0);
}

int	loop_of_philo_watch(t_var *my_var)
{
	int	i;

	i = 0;
	while (i < my_var->args[0] && my_var->dieing[i] != -1)
	{
		if ((gettime(my_var) - my_var->dieing[i])
			>= (*my_var->time_to_die / 1000))
		{
			pthread_mutex_lock(&my_var->m_print);
			*my_var->is_died = 1;
			printf("%d %d died \n", gettime(my_var), i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*philo_watch(void *var)
{
	t_var			*my_var;
	struct timeval	current_time;
	int				i;
	int				time_usec_to_die_to_zero;
	int				time_sec_to_di_to_zero;

	my_var = (t_var *) var;
	gettimeofday(&current_time, NULL);
	time_usec_to_die_to_zero = current_time.tv_usec;
	time_sec_to_di_to_zero = current_time.tv_sec;
	while (1)
	{
		gettimeofday(&current_time, NULL);
		usleep(100);
		i = 0;
		if (loop_of_philo_watch(my_var) == 1)
			return (0);
	}
	return (0);
}
