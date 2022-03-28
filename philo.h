/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:46:43 by brmohamm          #+#    #+#             */
/*   Updated: 2022/03/28 19:31:14 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct var_s
{
	int				*time_to_die;
	int				*time_to_eat;
	int				*time_to_sleep;
	int				*philo_must_eat;
	int				*dieing;
	int				*args;
	long			*utime_to_zero;
	long			*time_to_zero;

	int				*philo_num;
	int				*philo_cont;
	int				*is_died;
	pthread_mutex_t	m_philo_num;
	pthread_mutex_t	m_print;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_death;
}	t_var;

void	*philo_watch(void *var);
void	*philo_sleep(t_var *my_var, int philo_number);
void	*philo_eat(t_var *my_var, int philo_number);
int		ft_atoi(const char *str);
void	print_msg(char *word, t_var *my_var, int philo_number);
int		gettime(t_var *my_var);
int		*creat(t_var *var, char **argv, int argc, struct timeval *current_time);
int		philosophers_continue_the_code(t_var *my_var,
			int philo_number, int eating);
int		condetion_of_one_philo(t_var *my_var);
int		ft_isdigit(char *c);
#endif
