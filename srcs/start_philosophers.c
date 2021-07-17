#include "philo.h"

int	print_message(pthread_mutex_t print, unsigned long time, int num_philo, int identificator)
{
	pthread_mutex_lock(&print);
	if (identificator == 0)
		printf("%ld ms: %d has taken left fork\n", time, num_philo);
	if (identificator == 1)
		printf("%ld ms: %d has taken right fork\n", time, num_philo);
	if (identificator == 2)
		printf("%ld ms: %d has eating\n", time, num_philo);
	if (identificator == 3)
		printf("%ld ms: %d has sleeping\n", time, num_philo);
	if (identificator == 4)
		printf("%ld ms: %d has thinking\n", time, num_philo);
	if (identificator == 5)
		printf("%ld ms: %d has thinking\n", time, num_philo);
	if (identificator == 6)
		printf("%ld ms: %d died\n", time, num_philo);
	return (1);
}

void	*func(void *args)
{
	unsigned long	time;
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
		print_message(philo_info->print, time - start_info->start_time, philo_info->name, 0);
		pthread_mutex_lock(&tabel->forks[philo_info->right_fork]);
		time = get_time();
		print_message(philo_info->print, time - start_info->start_time, philo_info->name, 1);
		philo_info->time_start_eat = get_time();
		print_message(philo_info->print, time - start_info->start_time, philo_info->name, 2);
		my_sleep(start_info->time_to_eat);
		time = get_time();
		print_message(philo_info->print, time - start_info->start_time, philo_info->name, 3);
		pthread_mutex_unlock(&tabel->forks[philo_info->left_fork]);
		pthread_mutex_unlock(&tabel->forks[philo_info->right_fork]);
		my_sleep(start_info->time_to_sleep);
		time = get_time();
		print_message(philo_info->print, time - start_info->start_time, philo_info->name, 4);
		philo_info->life--;
	}
	return (NULL);
}

void	*check_die(void *args)
{
	t_philosofers **philo = (t_philosofers **)args;
	t_philosofers *phi = *philo;
	unsigned long now_time;
	int i = 0;
	while (1)
	{
		if (i == phi->start->num_of_pilo)
			i = 0;
		now_time = get_time();
		if (now_time - phi[i].philo_info->time_start_eat > phi->start->time_to_die)
		{
			print_message(phi[i].philo_info->print, now_time - phi[i].start->start_time, phi[i].philo_info->name, 6);
			return (0);
		}
		// printf("%d\n", phi[i].philo_info->life);
		if (phi[i].philo_info->life == 0)
		{
			write(1, "lol", 3);
			return (0);
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
	thread = (pthread_t *)malloc(sizeof(pthread_t) * (philo->start->num_of_pilo + 1));
	if (thread == NULL)
		return (0);
	while (i < philo->start->num_of_pilo)
	{
		pthread_create(&thread[i], NULL, &func, &philo[i]);
		pthread_detach(thread[i]);
		i++;
	}
	pthread_create(&thread[i], NULL, &check_die, &philo);
	pthread_join(thread[i], NULL);
	free(thread);
	return (1);
}