#include "philo.h"

void	free_philosophers(t_philosofers *philosophers)
{
	int i;
	int count;

	i = 0;
	count = philosophers->start->num_of_pilo;
	free(philosophers->philo_info);
	while (i < count)
	{
		pthread_mutex_destroy(philosophers[i].table->forks);
		i++;
	}
	free(philosophers->table->forks);
	free(philosophers->table);
	free(philosophers);
}

int	main(int argc, char **argv)
{
	t_philosofers *philosophers;

	if (argc == 5 || argc == 6)
	{
		philosophers = create_struct(argc, argv);
		if (philosophers == NULL)
			return (1);
		if (start_philosophers(philosophers) != 0)
			free_philosophers(philosophers);
		else
			return (1);
	}
	else
		write(1, "Wrong arguments!\n", 17);
	return (0);
}