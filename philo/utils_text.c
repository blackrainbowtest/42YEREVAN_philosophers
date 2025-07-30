/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 19:36:16 by root              #+#    #+#             */
/*   Updated: 2025/07/31 00:09:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		write_error("");
	if (*p_str == '\0')
		write_error("Input is empty or only spaces.");
	if (!is_digit(*p_str))
		write_error("Incorrect input! Use only digits.");
	p_number = p_str;
	while (is_digit(*p_str))
	{
		++len;
		++p_str;
	}
	if (len > 10)
		error_manager(EXIT_INT_ERROR);
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
		error_manager(EXIT_INT_ERROR);
	return (num);
}

void	write_message(t_table *table, long id, char *msg)
{
	pthread_mutex_lock(&(table->mtx_print));
	if (!(table->someone_died))
	{
		printf("%lli ", get_time() - table->start_time);
		printf("%ld ", id + 1);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(&(table->mtx_print));
	return ;
}
