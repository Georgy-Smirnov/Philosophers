#include "philo.h"

int check_str_is_pos_digit(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_argv_is_digit(int argc, char **argv)
{
	if (!check_str_is_pos_digit(argv[1]))
		return (0);
	if (!check_str_is_pos_digit(argv[2]))
		return (0);
	if (!check_str_is_pos_digit(argv[3]))
		return (0);
	if (!check_str_is_pos_digit(argv[4]))
		return (0);
	if (argc == 6)
	{
		if (!check_str_is_pos_digit(argv[5]))
			return (0);
	}
	return (1);
}

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

long	get_time()
{
        struct timeval time;
        gettimeofday(&time, NULL);
        return (time.tv_usec / 1000);
}

