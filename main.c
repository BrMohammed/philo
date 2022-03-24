#include "philo.h"
static void table_of_forks(var_t *var)
{
	int i;
	int number_of_forks;
	
	i = 0;
	number_of_forks = var->args[0];
	var->forks = malloc(number_of_forks * sizeof(int));
	var->forks[number_of_forks] = '\0';
	while(var->forks[i])
	{
		var->forks[i] = 1;
		i++;
	}
	// for(int i = 0; var->forks[i]; i++)
	// 	{
	// 		printf(" [%d] " ,var->forks[i]);
	// 	}
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


	var->time_to_die =  &var->args[1];
	var->time_to_eat =  &var->args[2];
	var->time_to_sleep =  &var->args[3];
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
	pthread_mutex_lock (&((var_t*)var)->m_philo_num);
	*my_var->philo_num = *my_var->philo_num + 1;
	philo_number = *my_var->philo_num;
	
	pthread_mutex_unlock (&my_var->m_philo_num);
	//while(1)
	//{
		if (my_var->forks[philo_number - 1] == 1 && ((my_var->forks[philo_number ] != '\0' && my_var->forks[philo_number] == 1 ) || (my_var->forks[philo_number ] == '\0' && my_var->forks[0] == 1 )))
		{
			pthread_mutex_lock (&my_var->m_can_eat);
			if(my_var->forks[philo_number] != '\0' && my_var->forks[0] == 1)
			{
				my_var->forks[philo_number - 1] = -1;
				my_var->forks[philo_number] = -1;
			}
			else if(my_var->forks[philo_number] == '\0' && my_var->forks[0] == 1)
			{
				my_var->forks[philo_number - 1] = -1;
				my_var->forks[0] = -1;
			}
		
				printf("fork : ");
				for(int i = 0; my_var->forks[i]; i++)
				{
					printf(" [%d] " ,my_var->forks[i]);
				}
				printf("\n");
			gettimeofday(&current_time, NULL);
			int time = ((current_time.tv_sec - *my_var->time_to_zero) * 1000) + (current_time.tv_usec - *my_var->utime_to_zero) / 1000;
			printf("\t%d %d is eating \n\n" ,time,philo_number);
			//sleep(1);
			if(my_var->forks[philo_number] != '\0' && my_var->forks[philo_number] == -1)
			{
				my_var->forks[philo_number - 1] = 1;
				my_var->forks[philo_number] = 1;
			}
			else if(my_var->forks[philo_number] == '\0' && my_var->forks[philo_number] == -1)
			{
				my_var->forks[philo_number - 1] = 1;
				my_var->forks[0] = 1;
			}
			pthread_mutex_unlock (&my_var->m_can_eat);
		}
		else 
		{
			gettimeofday(&current_time, NULL);
			int time1 = ((current_time.tv_sec - *my_var->time_to_zero) * 1000) + (current_time.tv_usec - *my_var->utime_to_zero) / 1000;
			printf("\t%d %d is slepping \n\n" ,time1,philo_number);
			//sleep(1);
		}
		// 	printf("fork : ");
		// for(int i = 0; my_var->forks[i]; i++)
		// {
		// 	printf(" [%d] " ,my_var->forks[i]);
		// }
		// printf("\n");
		
		
	
	//}
	
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
		pthread_mutex_init(&var.m_can_eat, NULL);
		var.args = creat(&var,argv,argc,&current_time);
		pthread_t th[*var.philo_cont];
		int i = 0;
		while(i++ < *var.philo_cont )
			pthread_create(&th[i],NULL,&philosophers,&var);
		i = 0;
		while(i++ < *var.philo_cont )
			pthread_join(th[i],NULL);
		pthread_mutex_destroy(&var.m_philo_num);
		pthread_mutex_destroy(&var.m_can_eat);
	}
	else if(argc > 6)
	{
		printf("to many args \n");
	}
	return (0);
}
