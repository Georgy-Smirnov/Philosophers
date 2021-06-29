#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_start_info
{
	int	num_of_pilo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_times_each_pilo_must_eat;
	long	start_time;
}				t_start_info;

typedef struct	s_philo_info
{
    int name;
    int left_fork;
    int right_fork;
}				t_philo_info;

typedef struct s_table
{
    pthread_mutex_t *forks;
} 				t_table;

typedef struct s_philosophers
{
	t_start_info *start;
	t_table *table;
	t_philo_info *philo_info;
}				t_philosofers;

t_philosofers *create_struct(int argc, char **argv);
int	start_philosophers(t_philosofers *philosophers);

int	ft_atoi(const char *str);
long	get_time();
int	check_argv_is_digit(int argc, char **argv);

#endif