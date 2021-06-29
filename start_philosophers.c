#include "philo.h"

void	*func(void *args)
{
	long	time;
	long	time_start_eat;
	pthread_mutex_t entry_point = PTHREAD_MUTEX_INITIALIZER;
	t_philosofers *arg = (t_philosofers *)args;
	t_table *tabel = arg->table;
	t_philo_info *philo_info = arg->philo_info;
	t_start_info * start_info = arg->start;
	int i;

	i = 0;
	while (1 != 2)
	{
		time = get_time();
		printf("%ld %d is thinking\n", time - start_info->start_time, philo_info->name);
		pthread_mutex_lock(&entry_point);
		pthread_mutex_lock(&tabel->forks[philo_info->left_fork]);
		pthread_mutex_lock(&tabel->forks[philo_info->right_fork]);
		pthread_mutex_unlock(&entry_point);
		time_start_eat = get_time();
		if (time - time_start_eat > start_info->time_to_die)
		{
			printf("%ld %d died\n", time - start_info->start_time, philo_info->name);
			pthread_mutex_unlock(&tabel->forks[philo_info->left_fork]);
			pthread_mutex_unlock(&tabel->forks[philo_info->right_fork]);
			exit(1);
		}
		printf("%ld %d has taken fork\n", time_start_eat - start_info->start_time, philo_info->name);
		usleep(1000 * start_info->time_to_eat);
		time = get_time();
		if (time - time_start_eat > start_info->time_to_die)
		{
			printf("%ld %d died\n", time - start_info->start_time, philo_info->name);
			pthread_mutex_unlock(&tabel->forks[philo_info->left_fork]);
			pthread_mutex_unlock(&tabel->forks[philo_info->right_fork]);
			exit(1);
		}
		printf("%ld %d has eating\n", time - start_info->start_time, philo_info->name);

		pthread_mutex_unlock(&tabel->forks[philo_info->left_fork]);
		pthread_mutex_unlock(&tabel->forks[philo_info->right_fork]);
		usleep(1000 * start_info->time_to_sleep);
		time = get_time();
		if (time - time_start_eat > start_info->time_to_die)
		{
			printf("%ld %d died\n", time - start_info->start_time, philo_info->name);
			exit(1);
		}
		printf("%ld %d has sleeping fork\n", time - start_info->start_time, philo_info->name);
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
	return (1);
}