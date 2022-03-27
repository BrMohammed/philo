/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brmohamm <brmohamm@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:46:47 by brmohamm          #+#    #+#             */
/*   Updated: 2022/03/27 20:42:09 by brmohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	condetion_of_one_philo(t_var *my_var)
{
	if (*my_var->philo_cont == 1)
	{
		while (1)
		{
			if (*my_var->is_died == 1)
				return (1);
		}
	}
	return (0);
}

static long	loop(const char *str, int i, int n)
{
	long	result;
	long	help;

	result = 0;
	help = 0;
	while (str[n] >= '0' && str[n] <= '9')
	{
		help = 10 * help + (str[n] - '0');
		if ((help / 10 != result) && (i == -1))
			return (0);
		if ((help / 10 != result) && (i == 1))
			return (-1);
		result = 10 * result + (str[n] - '0');
		n++;
	}
	return (result * i);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		i;
	int		n;

	result = 0;
	i = 1;
	n = 0;
	while (str[n] == '\f' || str[n] == '\n' || str[n] == 32
		|| str[n] == '\r' || str[n] == '\v' || str[n] == '\t')
		n++;
	if (str[n] == '-')
	{
		i *= -1;
		n++;
	}
	else if (str[n] == '+')
		n++;
	result = loop(str, i, n);
	return (result);
}
