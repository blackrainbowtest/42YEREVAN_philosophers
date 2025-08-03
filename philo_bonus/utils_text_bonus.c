/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_text_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:14:13 by root              #+#    #+#             */
/*   Updated: 2025/08/03 16:15:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	is_digit_str(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (false);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	ft_atoi(const char *str)
{
	long	num;

	num = 0;
	while (*str >= '0' && *str <= '9')
		num = num * 10 + (*str++ - '0');
	if (num > INT_MAX)
		return (-1);
	return ((int)num);
}