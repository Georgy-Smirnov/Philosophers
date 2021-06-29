#include "philo.h"

t_start_info *put_info_in_start(int argc, char **argv)
{
	t_start_info *start;
	long time;

	time = get_time();
	start = (t_start_info *)malloc(sizeof(t_start_info));
	if (start == NULL)
		return (NULL);
	if (!check_argv_is_digit(argc, argv))
	{
		write(1, "Arguments ERROR!\n", 17);
		return (NULL);
	}
	start->num_of_pilo = ft_atoi(argv[1]);
	start->time_to_die = ft_atoi(argv[2]);
	start->time_to_eat = ft_atoi(argv[3]);
	start->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		start->num_of_times_each_pilo_must_eat = ft_atoi(argv[5]);
	else
		start->num_of_times_each_pilo_must_eat = 0;
	start->start_time = time;
	return (start);
}

t_table *put_info_about_table(int count)
{
	t_table *table;
	int		i;

	i = 0;
	table = (t_table *)malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * count);
	if (table->forks == NULL)
		return (NULL);
	while (i < count)
	{
		if (pthread_mutex_init(&(table->forks[i]), NULL) != 0)
			return (NULL);
		i++;
	}
	return (table);
}

t_philo_info *put_info_in_philo(int count)
{
	t_philo_info *philo_info;
	int i;

	i = 0;
	philo_info = (t_philo_info *)malloc(sizeof(t_philo_info) * count);
	if (philo_info == NULL)
		return (NULL);
	while (i < count)
	{
		philo_info[i].name = i + 1;
		philo_info[i].left_fork = i;
		if (i == count - 1)
			philo_info[i].right_fork = 0;
		else
			philo_info[i].right_fork = i + 1;
		i++;
	}
	return (philo_info);

}

t_philosofers *create_struct(int argc, char **argv)
{
	t_philosofers	*philosopers;
	t_start_info	*start;
	t_table			*table;
	t_philo_info	*philo_info;
	int i;

	i = 0;
	start = put_info_in_start(argc, argv);
	if (start == NULL)
		return (NULL);
	table = put_info_about_table(start->num_of_pilo);
	if (table == NULL)
		return (NULL);
	philo_info = put_info_in_philo(start->num_of_pilo);
	if (philo_info == NULL)
		return (NULL);
	philosopers = (t_philosofers *)malloc(sizeof(t_philosofers) * start->num_of_pilo);
	if (philosopers == NULL)
		return (NULL);
	while (i < start->num_of_pilo)
	{
		philosopers[i].philo_info = &philo_info[i];
		philosopers[i].start = start;
		philosopers[i].table = table;
		i++;
	}
	return (philosopers);
}