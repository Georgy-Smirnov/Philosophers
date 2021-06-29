#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	rezult;
	int	checker;

	i = 0;
	rezult = 0;
	checker = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
	{
		checker = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		rezult *= 10;
		rezult += str[i] - 48;
		i++;
	}
	if (checker == 1)
		return (-rezult);
	return (rezult);
}

long            get_time()
{
        struct timeval time;
        gettimeofday(&time, NULL);
        return (time.tv_usec);
}

int	create_struct(t_all **all, int argc, char **argv)
{
	*all = (t_all *)malloc(sizeof(t_all));
	if (*all == NULL)
		return (0);
	(*all)->start = (t_start_data *)malloc(sizeof(t_start_data));
	if ((*all)->start == NULL)
		return (0);
	(*all)->start->start_time = get_time();
	(*all)->start->num_of_pilo = ft_atoi(argv[1]);
	(*all)->start->time_to_die = ft_atoi(argv[2]);
	(*all)->start->time_to_eat = ft_atoi(argv[3]);
	(*all)->start->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		(*all)->start->num_of_times_each_pilo_must_eat = ft_atoi(argv[5]);
	else
		(*all)->start->num_of_times_each_pilo_must_eat = -1;
	return (1);
}

int	init_forks(t_forks **table, t_start_data *data)
{
	int i;

	i = 0;
	*table = (t_forks *)malloc(sizeof(t_forks));
	if (*table == NULL)
		return (0);
	(*table)->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->num_of_pilo);
	if ((*table)->forks == NULL)
		return (0);
	while (i < data->num_of_pilo)
	{
		pthread_mutex_init(&((*table)->forks[i]), NULL);
		printf("forks_init %d\n", i);
		i++;
	}
	return (1);
}

int	init_philosophers(t_all *all)
{
	int i;
	i = 0;

	all->philosopher = (t_philosopher *)malloc(sizeof(t_philosopher) * all->start->num_of_pilo);
	if (all->philosopher == NULL)
		return (0);
	while (i < all->start->num_of_pilo)
	{
		all->philosopher[i].name = i + 1;
		all->philosopher[i].left_fork = i;
		if (i == all->start->num_of_pilo - 1)
			all->philosopher[i].right_fork = 0;
		else
			all->philosopher[i].right_fork = i + 1;
		i++;
	}
	return (1);
}

void	print_struct(t_all *all)
{
	int i = 0;
	printf("start time: %ld\n", all->start->start_time);
	printf("number of philosophers: %d\n", all->start->num_of_pilo);
	printf("time_to_die: %d\n", all->start->time_to_die);
	printf("time_to_eat: %d\n", all->start->time_to_eat);
	printf("time_to_sleep: %d\n", all->start->time_to_sleep);
	printf("[number_of_times_each_philosopher_must_eat]: %d\n", all->start->num_of_times_each_pilo_must_eat);
	printf("********************************************************\n");
	while (i < all->start->num_of_pilo)
	{
		printf("philosophers № %d has forks %d and %d\n", all->philosopher[i].name, all->philosopher[i].left_fork, all->philosopher[i].right_fork);
		i++;
	}
}

void	*eat(void *tmp)
{
	t_all *all = tmp;
	
	printf("%d filosophers start eat\n", all->philosopher[])
	return (NULL);
}



int	main(int argc, char **argv)
{
	t_philosofers *philosophers;
	int i;

	i = 0;
	if (argc == 5 || argc == 6)
	{
		philosophers = create_struct(argc, argv);
		if (philosophers == NULL)
			return (1);
		init_forks(&(all->forks), all->start);
		init_philosophers(all);
		print_struct(all);
		pt = (pthread_t *)malloc(sizeof(pthread_t) * all->start->num_of_pilo);
		if (pt == NULL)
			return (0);
		while (i < all->start->num_of_pilo)
		{
			pthread_create(&pt[i], NULL, &eat, (void *)all);
			i++;
		}
// 		*(data->i) = 0;
// 		while (*(data->i) < data->num_of_pilo)
// 		{
// 			pthread_join(pt[i], NULL);
// 			printf("Thread %d end!\n", *(data->i));
// 			(*(data->i))++;
// 		}
// 		pthread_mutex_destroy(&(data->mutex));
// 		sleep(3);
// 		// write (1, "END!\n", 5);
	}
	else
	{
		write(1, "Wrong arguments!\n", 17);
		return (0);
	}
}
