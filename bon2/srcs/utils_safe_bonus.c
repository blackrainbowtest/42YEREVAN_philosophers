#include "philo_bonus.h"

void	*safe_malloc(size_t bytes)
{
	void	*p_ret;

	p_ret = malloc(bytes);
	if (NULL == p_ret)
		error_exit("Error with the malloc");
	return (p_ret);
}