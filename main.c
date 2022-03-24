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
	// printf("micro seconds : %ld \n",((current_time.tv_sec - var.time_to_zero) + (current_time.tv_usec - var.utime_to_zero))); // print init
	// printf("micro seconds : %ld \n",(((current_time.tv_sec - var.time_to_zero) * 1000) + ((current_time.tv_usec - var.utime_to_zero) / 1000)));  // print time
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
	sleep(1);
	struct timeval current_time;
	var_t *my_var = (var_t*) var;
	gettimeofday(&current_time, NULL);
	int time = ((current_time.tv_sec - *my_var->time_to_zero) * 1000) + (current_time.tv_usec - *my_var->utime_to_zero) / 1000;
	printf("%d %d is sleeping \n" ,time,*my_var->philo_num);
	//free(var->philo);
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
		var.args = creat(&var,argv,argc,&current_time);
		pthread_t th[*var.forks];
		int i = 0;
		while(i < *var.forks )
		{
			var.philo_num =  malloc(sizeof(int));
			*var.philo_num = i + 1;
			pthread_create(&th[i],NULL,&philosophers,&var);
			i++;

		}
		i = 0;
		while(i < *var.forks )
		{
			pthread_join(th[i],NULL);
			i++;
		}
	}
	else if(argc > 6)
	{
		printf("to many args \n");
	}
	return (0);
}
