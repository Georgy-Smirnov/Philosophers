#include "philo.h"

void	free_philosophers(t_all *all)
{
	int	i;
	int	count;

	i = 0;
	count = all->count_philosophers;
	pthread_mutex_destroy(all->philo[0].print_mutex);
	while (i < count)
	{
		pthread_mutex_destroy(all->philo[i].left_fork);
		i++;
	}
	free(all->philo[0].print_mutex);
	free(all->philo[0].left_fork);
	free(all->philo);
	free(all);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc == 5 || argc == 6)
	{
		all = create_struct(argc, argv);
		if (all == NULL)
			return (1);
		if (start_philosophers(all) != 0)
			return (1);
		free_philosophers(all);
	}
	else
		printf("Wrong arguments!\n");
	return (0);
}
