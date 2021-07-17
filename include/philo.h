#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_start_info
{
	int				count_pilosophers;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				num_of_times_each_pilo_must_eat;
	unsigned long	programm_start_time;
}					t_start_info;

typedef struct s_philosophers
{
	int				num_of_pilo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				times_eat;
	unsigned long	start_time;
	unsigned long	last_eat_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
}					t_philosophers;

typedef struct s_all
{
	int				count_philosophers;
	t_philosophers	*philo;
}					t_all;

t_all			*create_struct(int argc, char **argv);
int				start_philosophers(t_all *all);
int				ft_atoi(const char *str);
unsigned long	get_time(void);
int				check_argv_is_digit(int argc, char **argv);
int				my_sleep(unsigned long time_to_sleep);

#endif