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
	long		len;
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

long	ft_atol(const char *p_str)
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