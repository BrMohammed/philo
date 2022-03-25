#include "philo.h"
static void table_of_forks(var_t *var)
{
	int i;
	int number_of_forks;
	
	i = 0;
	number_of_forks = var->args[0];
	var->forks = malloc(number_of_forks * sizeof(pthread_mutex_t));
}

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
	///alloc///
	var->time_to_die = malloc(sizeof(int));
	var->time_to_eat = malloc(sizeof(int));
	var->time_to_sleep = malloc(sizeof(int));
	var->utime_to_zero = malloc(sizeof(long));
	var->philo_cont = malloc(sizeof(int));
	var->time_to_zero = malloc(sizeof(long));
	var->philo_num =  malloc(sizeof(int));


	*var->time_to_die =  var->args[1] * 1000;
	*var->time_to_eat =  var->args[2] * 1000;
	*var->time_to_sleep =  var->args[3] * 1000;
	table_of_forks(var);
	var->philo_cont = &var->args[0];
	gettimeofday(current_time, NULL);
	*var->utime_to_zero = current_time->tv_usec;
	*var->time_to_zero = current_time->tv_sec;
	
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

	//gettimeofday(&current_time, NULL);
	var_t *my_var = (var_t*) var;
	pthread_mutex_lock (&my_var->m_philo_num);
	*my_var->philo_num = *my_var->philo_num + 1;
	philo_number = *my_var->philo_num;
	pthread_mutex_unlock (&my_var->m_philo_num);
	
	int t =0;
	while(t  < 2)
	{
		pthread_mutex_lock (&my_var->forks[philo_number -1]);
		if(philo_number == 5)
			pthread_mutex_lock (&my_var->forks[0]);
		else
			pthread_mutex_lock (&my_var->forks[philo_number]);
		
		gettimeofday(&current_time, NULL);
		int time = ((current_time.tv_sec - *my_var->time_to_zero) * 1000) + ((current_time.tv_usec - *my_var->utime_to_zero) / 1000);
		printf("\t%d %d is eating \n\n" ,time,philo_number);
		usleep(*my_var->time_to_eat);

		pthread_mutex_unlock (&my_var->forks[philo_number -1]);
		if(philo_number == 5)
			pthread_mutex_unlock (&my_var->forks[0]);
		else
			pthread_mutex_unlock (&my_var->forks[philo_number]);
		gettimeofday(&current_time, NULL);
		int time1 = ((current_time.tv_sec - *my_var->time_to_zero) * 1000) + (current_time.tv_usec - *my_var->utime_to_zero) / 1000;
		printf("\t%d %d is slepping \n\n" ,time1,philo_number);
		usleep(*my_var->time_to_sleep);
		t++;
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
		int i;
		struct timeval current_time;
		var_t var;

		var.args = creat(&var,argv,argc,&current_time);
		i = 0;
		pthread_mutex_init(&var.m_philo_num, NULL);
		while(i < *var.philo_cont)
		{
			pthread_mutex_init(&var.forks[i], NULL);
			i++;
		}
		i = 0;
		pthread_t th[*var.philo_cont];
		while(i++ < *var.philo_cont )
		{
			pthread_create(&th[i],NULL,&philosophers,&var);
			usleep(100);
		}
		i = 0;
		while(i++ < *var.philo_cont )
			pthread_join(th[i],NULL);
		pthread_mutex_destroy(&var.m_philo_num);
		i = 0;
		while(i < *var.philo_cont)
		{
			pthread_mutex_destroy(&var.forks[i]);
			i++;
		}
		
	}
	else if(argc > 6)
	{
		printf("to many args \n");
	}
	return (0);
}
