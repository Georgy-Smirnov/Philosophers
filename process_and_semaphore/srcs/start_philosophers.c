#include "philo.h"

void	*check_die(void *args)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)args;
	while (1)
	{
		if (get_time() - philo->last_eat_time > philo->time_to_die)
		{
			sem_wait(philo->print);
			printf("%ld ms: %d has died \n", get_time() \
				- philo->start_time, philo->num_of_pilo);
			exit (EXIT_FAILURE);
		}
		usleep(250);
	}
	return (NULL);
}

int	start_process(t_all *all, int i)
{
	t_philosophers	*philo;
	pthread_t		checker;

	philo = &(all->philo[i]);
	if (pthread_create(&checker, NULL, &check_die, \
		(void *)&(all->philo[i])) != 0)
		exit (EXIT_FAILURE);
	if (all->count_philosophers / 2 < philo->num_of_pilo)
		my_sleep(philo->time_to_eat - 10);
	while (philo->times_eat != 0)
	{
		if (get_forks(philo) != 0)
			exit (EXIT_FAILURE);
		if (philo_actions(philo) != 0)
			exit (EXIT_FAILURE);
		if (philo->times_eat != -1 && philo->times_eat != 0)
			philo->times_eat--;
	}
	exit (EXIT_SUCCESS);
}

void	end_process(t_all *all, pid_t *pid, int status)
{
	int	i;

	i = 0;
	if (WEXITSTATUS(status))
	{
		while (i < all->count_philosophers)
		{
			kill(pid[i], SIGKILL);
			i++;
		}
	}
	else
	{
		while (i < all->count_philosophers - 1)
		{
			waitpid(0, NULL, 0);
			i++;
		}
	}
	free(pid);
}

int	start_philosophers(t_all *all)
{
	int		i;
	pid_t	*pid;
	int		status;

	i = 0;
	pid = (pid_t *)malloc(sizeof(pid_t) * all->count_philosophers);
	if (pid == NULL)
		return (1);
	while (i < all->count_philosophers)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (1);
		if (pid[i] == 0)
			start_process(all, i);
		i++;
	}
	waitpid(0, &status, 0);
	end_process(all, pid, status);
	return (0);
}
