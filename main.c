#include "philo.h"

void	print_struct(t_philosofers *philo)
{
	int i = 0;
	int count = philo[0].start->num_of_pilo;
	printf("********* start ********\n");
	printf("num_of_filo: %d\n", philo[i].start->num_of_pilo);
	printf("time to die: %d\n", philo[i].start->time_to_die);
	printf("time to eat: %d\n", philo[i].start->time_to_eat);
	printf("time to sleap: %d\n", philo[i].start->time_to_sleep);
	printf("times: %d\n", philo[i].start->num_of_times_each_pilo_must_eat);
	printf("time start: %ld\n", philo[i].start->start_time);
	while (i < count)
	{
		printf("******** philo_info *********\n");
		printf("name: %d left-%d right-%d\n", philo[i].philo_info->name, philo[i].philo_info->left_fork, philo[i].philo_info->right_fork);
		printf("*****************************\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philosofers *philosophers;

	if (argc == 5 || argc == 6)
	{
		philosophers = create_struct(argc, argv);
		if (philosophers == NULL)
			return (1);
		// print_struct(philosophers);
		// sleep(1);
		start_philosophers(philosophers);
	}
	else
	{
		write(1, "Wrong arguments!\n", 17);
		return (0);
	}
}