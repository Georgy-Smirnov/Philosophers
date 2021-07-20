#include "philo.h"

void	free_philosophers(t_all *all)
{
	sem_close(all->philo->forks);
	sem_close(all->philo->print);
	sem_unlink(FORKS);
	sem_unlink(PRINT);
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
