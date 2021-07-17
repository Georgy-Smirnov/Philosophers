#include "philo.h"

void	*func(void *args)
{
	unsigned long	time;
	unsigned long	time_start_eat;
	t_philosofers *arg = (t_philosofers *)args;
	t_table *tabel = arg->table;
	t_philo_info *philo_info = arg->philo_info;
	t_start_info *start_info = arg->start;
	int i;

	i = 0;
	if (philo_info->name % 2 == 1)
		usleep(100);
	while (1 != 2)
	{
		pthread_mutex_lock(&tabel->forks[philo_info->left_fork]);
		time = get_time();
		printf("%ld %d has taken %d fork\n", time - start_info->start_time, philo_info->name, philo_info->left_fork);
		pthread_mutex_lock(&tabel->forks[philo_info->right_fork]);
		time = get_time();
		printf("%ld %d has taken %d fork\n", time - start_info->start_time, philo_info->name, philo_info->right_fork);
		time_start_eat = get_time();
		if (time - time_start_eat > (unsigned long)start_info->time_to_die)
		{
			printf("%ld %d died\n", time - start_info->start_time, philo_info->name);
			pthread_mutex_unlock(&tabel->forks[philo_info->left_fork]);
			pthread_mutex_unlock(&tabel->forks[philo_info->right_fork]);
			exit(1);
		}
		printf("%ld %d has eateng\n", time_start_eat - start_info->start_time, philo_info->name);
		my_sleep(start_info->time_to_eat);
		time = get_time();
		if (time - time_start_eat > (unsigned long)start_info->time_to_die)
		{
			printf("%ld %d died\n", time - start_info->start_time, philo_info->name);
			pthread_mutex_unlock(&tabel->forks[philo_info->left_fork]);
			pthread_mutex_unlock(&tabel->forks[philo_info->right_fork]);
			exit(1);
		}
		printf("%ld %d has sleeping\n", time - start_info->start_time, philo_info->name);
		pthread_mutex_unlock(&tabel->forks[philo_info->left_fork]);
		pthread_mutex_unlock(&tabel->forks[philo_info->right_fork]);
		my_sleep(start_info->time_to_sleep);
		time = get_time();
		if (time - time_start_eat > (unsigned long)start_info->time_to_die)
		{
			printf("%ld %d died\n", time - start_info->start_time, philo_info->name);
			exit(1);
		}
		printf("%ld %d has thinking\n", time - start_info->start_time, philo_info->name);
		if (start_info->num_of_times_each_pilo_must_eat != 0)
		{
			if (i == start_info->num_of_times_each_pilo_must_eat)
				return (NULL);
		}
		i++;
	}
	return (NULL);
}

int	start_philosophers(t_philosofers *philo)
{
	pthread_t *thread;
	int i;

	i = 0;
	thread = (pthread_t *)malloc(sizeof(pthread_t) * philo->start->num_of_pilo);
	if (thread == NULL)
		return (0);
	while (i < philo->start->num_of_pilo)
	{
		pthread_create(&thread[i], NULL, &func, &philo[i]);
		i++;
	}
	i = 0;
	while (i < philo->start->num_of_pilo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	free(thread);
	return (1);
}