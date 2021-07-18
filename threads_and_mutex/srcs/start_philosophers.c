#include "philo.h"

int	get_forks(t_philosophers *philo)
{
	if (pthread_mutex_lock(philo->right_fork) != 0)
		return (1);
	if (pthread_mutex_lock(philo->print_mutex) != 0)
		return (1);
	printf("%ld ms: %d has taken right fork\n", get_time() \
		- philo->start_time, philo->num_of_pilo);
	if (pthread_mutex_unlock(philo->print_mutex) != 0)
		return (1);
	if (pthread_mutex_lock(philo->left_fork) != 0)
		return (1);
	if (pthread_mutex_lock(philo->print_mutex) != 0)
		return (1);
	printf("%ld ms: %d has taken left fork\n", get_time() \
		- philo->start_time, philo->num_of_pilo);
	if (pthread_mutex_unlock(philo->print_mutex) != 0)
		return (1);
	return (0);
}

int	actions_philo(t_philosophers *philo)
{
	philo->last_eat_time = get_time();
	if (pthread_mutex_lock(philo->print_mutex) != 0)
		return (1);
	printf("%ld ms: %d has eating\n", get_time() \
		- philo->start_time, philo->num_of_pilo);
	if (pthread_mutex_unlock(philo->print_mutex) != 0)
		return (1);
	my_sleep(philo->time_to_eat);
	if (pthread_mutex_unlock(philo->right_fork) != 0 \
		|| pthread_mutex_unlock(philo->left_fork) != 0)
		return (1);
	if (pthread_mutex_lock(philo->print_mutex) != 0)
		return (1);
	printf("%ld ms: %d has sleeping\n", get_time() \
		- philo->start_time, philo->num_of_pilo);
	if (pthread_mutex_unlock(philo->print_mutex) != 0)
		return (1);
	my_sleep(philo->time_to_sleep);
	if (pthread_mutex_lock(philo->print_mutex) != 0)
		return (1);
	printf("%ld ms: %d has thinking\n", get_time() \
		- philo->start_time, philo->num_of_pilo);
	if (pthread_mutex_unlock(philo->print_mutex) != 0)
		return (1);
	return (0);
}

void	*func(void *args)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)args;
	if (philo->num_of_pilo % 2 == 1)
		my_sleep(philo->time_to_eat - 10);
	while (1 != 2)
	{
		if (get_forks(philo) != 0)
			return (NULL);
		if (actions_philo(philo) != 0)
			return (NULL);
		if (philo->times_eat != -1 && philo->times_eat != 0)
			philo->times_eat--;
	}
	return (NULL);
}

void	*check_die(void *args)
{
	t_all	*a;
	int		i;

	a = (t_all *)args;
	i = 0;
	while (1)
	{
		if (i == a->count_philosophers)
			i = 0;
		if (a->philo[i].times_eat == 0)
		{
			pthread_mutex_lock(a->philo[i].print_mutex);
			return (NULL);
		}
		if (get_time() - a->philo[i].last_eat_time > a->philo[i].time_to_die)
		{
			if (pthread_mutex_lock(a->philo[i].print_mutex) != 0)
				return (NULL);
			printf("%ld ms: %d has died\n", get_time() \
				- a->philo[i].start_time, a->philo[i].num_of_pilo);
			return (NULL);
		}	
		i++;
	}
	return (NULL);
}

int	start_philosophers(t_all *all)
{
	pthread_t	*thread;
	pthread_t	checker;
	int			i;

	i = 0;
	if (pthread_create(&checker, NULL, &check_die, (void *)all) != 0)
		return (1);
	thread = (pthread_t *)malloc(sizeof(pthread_t) * (all->count_philosophers));
	if (thread == NULL)
		return (1);
	while (i < all->count_philosophers)
	{
		if (pthread_create(&thread[i], NULL, &func, \
			(void *)&(all->philo[i])) != 0)
			return (1);
		if (pthread_detach(thread[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_join(checker, NULL) != 0)
		return (1);
	free(thread);
	return (0);
}
