#include "philo_bonus.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

static const char	*valid_input(const char *p_str)
{
	int			len;
	const char	*p_number;

	len = 0;
	while (is_space(*p_str))
		++p_str;
	if (*p_str == '+')
		++p_str;
	else if (*p_str == '-')
		error_exit("You can't handle negative numbers! Use positive ones.");
	if (*p_str == '\0')
		error_exit("Input is empty or only spaces.");
	if (!is_digit(*p_str))
		error_exit("Incorrect input! Use only digits.");
	p_number = p_str;
	while (is_digit(*p_str))
	{
		++len;
		++p_str;	
	}
	if (len > 10)
		error_exit("The value is too big, INT_MAX is the limit. "
			"Use less than 10 digits.");
	return (p_number);
}

static long	ft_atol(const char *p_str)
{
	long	num;

	num = 0;
	p_str = valid_input(p_str);
	while (is_digit(*p_str))
		num = (num * 10) + (*p_str++ - '0');
	if (num > INT_MAX)
		error_exit("The value is too big, INT_MAX is the limit. "
			"Use less than 10 digits.");
	return (num);
}

void	parse_input(t_table *p_table, char **argv)
{
	p_table->philo_nbr = ft_atol(argv[1]);
	p_table->time_to_die = ft_atol(argv[2]) * 1e3;
	p_table->time_to_eat = ft_atol(argv[3]) * 1e3;
	p_table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (p_table->time_to_die < 6e4
		|| p_table->time_to_eat < 6e4
		|| p_table->time_to_sleep < 6e4)
		error_exit("Time to die, eat or sleep must be more than 60ms.");
	if (argv[5])
		p_table->number_of_limit_meals = ft_atol(argv[5]);
	else
		p_table->number_of_limit_meals = -1;
}
