#include "philo.h"

int	get_forks(t_philosophers *philo)
{
	if (sem_wait(philo->forks) != 0)
		return (1);
	if (sem_wait(philo->print) != 0)
		return (1);
	printf("%ld ms: %d has taken fork\n", get_time() \
		- philo->start_time, philo->num_of_pilo);
	if (sem_post(philo->print) != 0)
		return (1);
	if (sem_wait(philo->forks) != 0)
		return (1);
	if (sem_wait(philo->print) != 0)
		return (1);
	printf("%ld ms: %d has taken fork\n", get_time() \
		- philo->start_time, philo->num_of_pilo);
	if (sem_post(philo->print) != 0)
		return (1);
	if (sem_wait(philo->print) != 0)
		return (1);
	printf("%ld ms: %d eating\n", get_time() \
		- philo->start_time, philo->num_of_pilo);
	if (sem_post(philo->print) != 0)
		return (1);
	return (0);
}

int	philo_actions(t_philosophers *philo)
{
	philo->last_eat_time = get_time();
	my_sleep(philo->time_to_eat);
	if (sem_post(philo->forks) != 0)
		return (1);
	if (sem_post(philo->forks) != 0)
		return (1);
	if (sem_wait(philo->print) != 0)
		return (1);
	printf("%ld ms: %d sleeping\n", get_time() \
		- philo->start_time, philo->num_of_pilo);
	if (sem_post(philo->print) != 0)
		return (1);
	my_sleep(philo->time_to_sleep);
	if (sem_wait(philo->print) != 0)
		return (1);
	printf("%ld ms: %d thinking\n", get_time() \
		- philo->start_time, philo->num_of_pilo);
	if (sem_post(philo->print) != 0)
		return (1);
	return (0);
}
