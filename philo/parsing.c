/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:01:42 by root              #+#    #+#             */
/*   Updated: 2025/07/13 18:47:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Checks whether the passed value is a number or not.
 * 
 * This function checks if the character is a digit (0-9).
 * 
 * @param c The character to check.
 * @return Returns true if the character is a digit, false otherwise. 
 */
static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/**
 * @brief Checks whether the passed value is a whitespace character.
 * 
 * This function checks if the character is a whitespace character,
 * 
 * @param c The character to check.
 * @return Returns true if the character is a whitespace, false otherwise.
 */
static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 31 == c);
}

/**
 * @brief Validates the input string for parsing.
 * 
 * This function checks if the input string is a valid number,
 * ensuring it does not contain negative values, non-digit characters,
 * and that it does not exceed the maximum length for an integer.
 * 
 * @param str The input string to validate.
 * @return Returns a pointer to the valid number part of the string.
 */
static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("You can't handle negative numbers! Use positive ones.");
	if (!is_digit(*str))
		error_exit("Incorrect input! Use only digits.");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("The value is too big, INT_MAX is the limit. "
			"Use less than 10 digits.");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10) + (*str++ - '0');
	if (num > INT_MAX)
		error_exit("The value is too big, INT_MAX is the limit. "
			"Use less than 10 digits.");
	return (num);
}

/**
 * ./philo 	5 		800 	200 	200 	[5]
 * 			argv[1]	argv[2]	argv[3]	argv[4]	argv[5]
 * 1) actual numbers
 * 2) not > INT_MAX
 * 3) timestamps > 60ms
 * usleep wants microseconds
 */
void	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]) * 1e3;
	table->time_to_eat = ft_atol(argv[3]) * 1e3;
	table->time_to_sleep = ft_atol(argv[4]) * 1e3;
	if (table->time_to_die < 6e4
		|| table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4)
		error_exit("Use timestamps major than 60ms");
	if (argv[5])
		table->number_of_limit_meals = ft_atol(argv[5]);
	else
		table->number_of_limit_meals = -1;
}
