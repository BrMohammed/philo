/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:46:35 by brmohamm          #+#    #+#             */
/*   Updated: 2022/03/27 17:37:53 by brmohamm         ###   ########.fr       */
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

static int	*creat(t_var *var, char **argv, int argc,
					struct timeval *current_time)
{
	int	i;

	i = 0;
	var->args = malloc(argc * sizeof(int));
	var->args[argc] = '\0';
	while (argv[++i])
		var->args[i - 1] = ft_atoi(argv[i]);
	if (var->args[1] <= 10)
	{
		printf("number to die must be more than 10ms\n");
		exit(0);
	}
	allocation(var);
	*var->time_to_die = var->args[1] * 1000;
	*var->time_to_eat = var->args[2] * 1000;
	*var->time_to_sleep = var->args[3] * 1000;
	if (var->args[4])
		*var->philo_must_eat = var->args[4];
	table_of_forks_and_dieing(var);
	var->philo_cont = &var->args[0];
	gettimeofday(current_time, NULL);
	*var->utime_to_zero = current_time->tv_usec;
	*var->time_to_zero = current_time->tv_sec;
	return (var->args);
}

static int	gettime(t_var *my_var)
{
	int				time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = ((current_time.tv_sec - *my_var->time_to_zero) * 1000) + ((current_time.tv_usec - *my_var->utime_to_zero) / 1000);
	return (time);
}

void	print_msg(char *word, t_var *my_var, int philo_number)
{
	pthread_mutex_lock (&my_var->m_print);
	printf("%d %d %s \n", gettime(my_var), philo_number, word);
	pthread_mutex_unlock (&my_var->m_print);
}

static void	*philo_eat(t_var *my_var, int philo_number)
{
	int	i;

	if (*my_var->is_died == 1)
		return (0);
	print_msg("is eating", my_var, philo_number);
	i = gettime(my_var);
	while (gettime(my_var) - i < (*my_var->time_to_eat / 1000));
	if (*my_var->is_died == 1)
		return (0);
	return (0);
}

void	*philo_sleep(t_var *my_var, int philo_number)
{
	int	i;

	if (*my_var->is_died == 1)
		return (0);
	print_msg("is slepping", my_var, philo_number);
	i = gettime(my_var);
	while (gettime(my_var) - i < *my_var->time_to_sleep / 1000);
	if (*my_var->is_died == 1)
	{
		usleep(100);
		return (0);
	}
	print_msg("is thinking", my_var, philo_number);
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
		usleep(1000);
		i = 0;
		while (i < *my_var->philo_cont && my_var->dieing[i] != -1)
		{
			if ((gettime(my_var) - my_var->dieing[i]) >= (*my_var->time_to_die / 1000))
			{
				print_msg("died", my_var, i + 1);
				*my_var->is_died = 1;
				return (0);
			}
			i++;
		}
	}
	return (0);
}

int	philosophers_continue_the_code(t_var *my_var,int philo_number,int eating)
{
	pthread_mutex_lock (&my_var->forks[philo_number -1]);
	if (*my_var->is_died == 1)
		return (0);
	print_msg("has taken a fork", my_var, philo_number);
	if (philo_number == *my_var->philo_cont)
	{
		pthread_mutex_lock (&my_var->forks[0]);
		print_msg("has taken a fork", my_var, philo_number);
	}
	else
	{
		pthread_mutex_lock (&my_var->forks[philo_number]);
		print_msg("has taken a fork", my_var, philo_number);
	}
	my_var->dieing[philo_number - 1] = gettime(my_var);
	philo_eat(my_var, philo_number);
	eating++;
	pthread_mutex_unlock (&my_var->forks[philo_number -1]);
	if (philo_number == *my_var->philo_cont)
		pthread_mutex_unlock (&my_var->forks[0]);
	else
		pthread_mutex_unlock (&my_var->forks[philo_number]);
	return (eating);
}

void	*philosophers(void *var)
{
	int		philo_number;
	int		time;
	t_var	*my_var;
	int		eating;

	my_var = (t_var *) var;
	pthread_mutex_lock (&my_var->m_philo_num);
	*my_var->philo_num = *my_var->philo_num + 1;
	philo_number = *my_var->philo_num;
	pthread_mutex_unlock (&my_var->m_philo_num);
	eating = 0;
	while (1)
	{
		if (*my_var->philo_must_eat)
		{
			if (eating == *my_var->philo_must_eat)
			{
				my_var->dieing[philo_number - 1] = -1;
				break ;
			}
		}
		eating = philosophers_continue_the_code(my_var,philo_number,eating);
		philo_sleep(my_var, philo_number);
		if (*my_var->is_died == 1)
			return (0);
	}
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
	int					i;
	struct timeval		current_time;
	pthread_t			*th;
	pthread_t			wth;
	t_var				var;

	if (argc > 4 && argc <= 6)
	{
		th = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
		var.args = creat(&var, argv, argc, &current_time);
		parse(th, wth, &var);
		threads(th, wth, &var);
	}
	else if (argc > 6)
		printf("to many args \n");
	return (0);
}
