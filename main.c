#include "philo.h"

static int* creat(var_t *var,char **argv, int argc,struct timeval *current_time)
{
	int i;
	
	i = 0;
	var->args = malloc(argc - 1 * sizeof(int));
	while(argv[++i])
		var->args[i - 1] = ft_atoi(argv[i]);
	if(var->args[1] < 10)
	{
		printf("number to die must be more than 10ms\n");
		exit(0);
	}
	if(var->args[0] < 2)
	{
		printf("number of philo must be more than 1 \n");
		exit(0);
	}
	var->forks = malloc(sizeof(int));
	var->forks = &var->args[0];
	gettimeofday(current_time, NULL);
	var->utime_to_zero = malloc(sizeof(long));
	*var->utime_to_zero = current_time->tv_usec;
	var->time_to_zero = malloc(sizeof(long));
	*var->time_to_zero = current_time->tv_sec;
	var->philo_num =  malloc(sizeof(int));
	return (var->args);
}

void print()
{
	int time;
	int philo;

	printf("%d %d has taken a fork \n",time,philo);
	printf("%d %d is eating \n",time,philo);
	printf("%d %d is sleeping \n",time,philo);
	printf("%d %d is thinking \n",time,philo);
	printf("%d %d died \n",time,philo);
}

void* philosophers(void *var)
{
	struct timeval current_time;
	int philo_number;
	pthread_mutex_lock (&((var_t*)var)->m_philo_num);
	*((var_t*)var)->philo_num = *((var_t*)var)->philo_num + 1;
	philo_number = *((var_t*)var)->philo_num;
	pthread_mutex_unlock (&((var_t*)var)->m_philo_num);
	while(1)
	{
		printf("========= is running ============= \n");
		sleep(1);
		gettimeofday(&current_time, NULL);
		int time = ((current_time.tv_sec - *((var_t*)var)->time_to_zero) * 1000) + (current_time.tv_usec - *((var_t*)var)->utime_to_zero) / 1000;
		printf("%d %d is sleeping \n" ,time,philo_number);
	}
	
	return (0);
}

void philo_eat()
{
	
}
void philo_sleep()
{
	
}
int main(int argc, char** argv)
{
	if (argc > 4 && argc <= 6)
	{
		struct timeval current_time;
		var_t var;
		pthread_mutex_init(&var.m_philo_num, NULL);
		var.args = creat(&var,argv,argc,&current_time);
		pthread_t th[*var.forks];
		int i = 0;
		while(i++ < *var.forks )
			pthread_create(&th[i],NULL,&philosophers,&var);
		i = 0;
		while(i++ < *var.forks )
			pthread_join(th[i],NULL);
		pthread_mutex_destroy(&var.m_philo_num);
	}
	else if(argc > 6)
	{
		printf("to many args \n");
	}
	return (0);
}
