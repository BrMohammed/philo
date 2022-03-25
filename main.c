#include "philo.h"
static void table_of_forks_and_dieing(var_t *var)
{
	int i;
	int number_of_forks;
	
	number_of_forks = var->args[0];
	var->forks = malloc(number_of_forks * sizeof(pthread_mutex_t));

	var->dieing = malloc(number_of_forks * sizeof(int));
	i = 0;
	while(i < number_of_forks)
	{
		var->dieing[i] = 0;
		i++;
	}


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
	table_of_forks_and_dieing(var);
	
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
static int gettime(var_t *my_var)
{
	int time;
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	time = ((current_time.tv_sec - *my_var->time_to_zero) * 1000) + ((current_time.tv_usec - *my_var->utime_to_zero) / 1000);
	return(time);
}
static void philo_eat(var_t *my_var,int philo_number)
{
	int time;

	time = gettime(my_var);
	printf("%d %d has taken a fork \n" ,time,philo_number);
	time = gettime(my_var);
	printf("%d %d is eating \n" ,time,philo_number);
	usleep(*my_var->time_to_eat);
}

void philo_sleep(var_t *my_var,int philo_number)
{
	int time;

	time = gettime(my_var);
	printf("%d %d is slepping \n" ,time,philo_number);
	usleep(*my_var->time_to_sleep);
	time = gettime(my_var);
	printf("%d %d is thinking \n" ,time,philo_number);
}
void* philo_watch(void *var)
{
	var_t *my_var = (var_t*) var;
	struct timeval current_time;
	int time;

	int real_time;

	int time_to_zero;
	int time_usec_to_die_to_zero;
	int time_sec_to_di_to_zero;

	int time_usec_to_die_to_zero2;
	int time_sec_to_di_to_zero2;

	gettimeofday(&current_time, NULL);

	time_usec_to_die_to_zero = current_time.tv_usec;
	time_sec_to_di_to_zero = current_time.tv_sec;


	time_usec_to_die_to_zero2 = current_time.tv_usec;
	time_sec_to_di_to_zero2 = current_time.tv_sec; 
	while(1)
	{
		gettimeofday(&current_time, NULL);
		real_time = ((current_time.tv_sec - time_sec_to_di_to_zero2) * 1000) + ((current_time.tv_usec - time_usec_to_die_to_zero2) / 1000);
		time = ((current_time.tv_sec - time_sec_to_di_to_zero) * 1000) + ((current_time.tv_usec - time_usec_to_die_to_zero) / 1000);
		time_to_zero += time*1.26;
		int i = 0;
		while(i < *my_var->philo_cont)
		{
			my_var->dieing[i] += time*1.26;
			i++;
		}
		time_usec_to_die_to_zero = current_time.tv_usec;
		time_sec_to_di_to_zero = current_time.tv_sec;
		usleep(1000);
		i = 0;
		while(i < *my_var->philo_cont)
		{
			if(my_var->dieing[i] == *my_var->time_to_die / 1000)
			{
				printf("%d %d died\n",real_time,i + 1);
				i++;
				exit(0);
			}
			i++;
		}
		
		
	}
	return(0);
}
void* philosophers(void *var)
{
	
	int philo_number;
	int time;
	var_t *my_var = (var_t*) var;

	pthread_mutex_lock (&my_var->m_philo_num);
	*my_var->philo_num = *my_var->philo_num + 1;
	philo_number = *my_var->philo_num;
	pthread_mutex_unlock (&my_var->m_philo_num);
	
	//int t = 0;
	while(1)
	{
		/*lock mutex*/
			pthread_mutex_lock (&my_var->forks[philo_number -1]);
			if(philo_number == *my_var->philo_cont)
				pthread_mutex_lock (&my_var->forks[0]);
			else
				pthread_mutex_lock (&my_var->forks[philo_number]);
			/**/

			philo_eat(my_var,philo_number);
			my_var->dieing[philo_number - 1] = 0;
			
			/*unlock mutex*/
			pthread_mutex_unlock (&my_var->forks[philo_number -1]);
			if(philo_number == *my_var->philo_cont)
				pthread_mutex_unlock (&my_var->forks[0]);
			else
				pthread_mutex_unlock (&my_var->forks[philo_number]);
			/**/

			philo_sleep(my_var,philo_number);
			//t++;
	}
	
	return (0);
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
		pthread_t wth;
		pthread_create(&wth,NULL,&philo_watch,&var);
		while(i++ < *var.philo_cont )
		{
			pthread_create(&th[i],NULL,&philosophers,&var);
			usleep(1);
		}
		i = 0;
		while(i++ < *var.philo_cont )
		{
			pthread_join(th[i],NULL);
		}
		pthread_join(wth,NULL);
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
