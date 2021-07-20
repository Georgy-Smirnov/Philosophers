#include "philo.h"

t_start_info	*put_info_in_start(int argc, char **argv)
{
	t_start_info	*start;

	start = (t_start_info *)malloc(sizeof(t_start_info));
	if (start == NULL)
		return (NULL);
	if (!check_argv_is_digit(argc, argv))
	{
		printf("Wrong arguments!\n");
		return (NULL);
	}
	start->count_pilosophers = ft_atoi(argv[1]);
	start->time_to_die = (unsigned long)ft_atoi(argv[2]);
	start->time_to_eat = (unsigned long)ft_atoi(argv[3]);
	start->time_to_sleep = (unsigned long)ft_atoi(argv[4]);
	if (argc == 6)
		start->num_of_times_each_pilo_must_eat = ft_atoi(argv[5]);
	else
		start->num_of_times_each_pilo_must_eat = -1;
	start->programm_start_time = get_time();
	return (start);
}

void	put_info_in_philo(t_philosophers *philo, t_start_info *start, int i)
{
	philo[i].num_of_pilo = i + 1;
	philo[i].time_to_die = start->time_to_die;
	philo[i].time_to_eat = start->time_to_eat;
	philo[i].time_to_sleep = start->time_to_sleep;
	philo[i].times_eat = start->num_of_times_each_pilo_must_eat;
	philo[i].start_time = start->programm_start_time;
	philo[i].last_eat_time = start->programm_start_time;
}

t_philosophers	*put_info_in_philosophers(t_start_info	*start)
{
	t_philosophers	*philo;
	sem_t			*forks;
	sem_t			*print;
	int				i;

	i = 0;
	sem_unlink(FORKS);
	sem_unlink(PRINT);
	philo = (t_philosophers *)malloc(sizeof(t_philosophers) \
		* start->count_pilosophers);
	if (philo == NULL)
		return (NULL);
	forks = sem_open(FORKS, O_CREAT, 0777, start->count_pilosophers);
	print = sem_open(PRINT, O_CREAT, 0777, 1);
	if (forks == SEM_FAILED || print == SEM_FAILED)
		return (NULL);
	while (i < start->count_pilosophers)
	{
		put_info_in_philo(philo, start, i);
		philo[i].forks = forks;
		philo[i].print = print;
		i++;
	}
	return (philo);
}

t_all	*create_struct(int argc, char **argv)
{
	t_all			*all;
	t_start_info	*start;
	t_philosophers	*philo;
	int				i;

	i = 0;
	start = put_info_in_start(argc, argv);
	if (start == NULL)
		return (NULL);
	all = (t_all *)malloc(sizeof(t_all));
	if (all == NULL)
		return (NULL);
	philo = put_info_in_philosophers(start);
	if (philo == NULL)
		return (NULL);
	all->count_philosophers = start->count_pilosophers;
	all->philo = philo;
	free(start);
	return (all);
}


