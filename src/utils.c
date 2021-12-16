/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:07:28 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/09 04:46:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_convert_str_to_int(char *str)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] != '+')
		{
			if (i != 0)
				res *= 10;
			res += str[i] - '0';
		}
		++i;
	}
	return (res);
}

int	ph_get_diff_between_start_and_curr_time(t_env *env, size_t *time_diff)
{
	size_t	start_time;
	size_t	curr_time;

	start_time = env->time.start;
	if (ph_gettime(env, &curr_time) == ERROR)
		return (ERROR);
	*time_diff = curr_time - start_time;
	return (SUCCESS);
}

void	ph_put_nbr_to_stderr(size_t nbr)
{
	size_t	nbr_in_char;

	if (nbr < 10)
	{
		nbr_in_char = nbr + '0';
		write(STDERR_FILENO, &nbr_in_char, 1);
	}
	else if (nbr > 9)
	{
		ph_put_nbr_to_stderr(nbr / 10);
		ph_put_nbr_to_stderr(nbr % 10);
	}
}

bool	ph_is_numeric(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '+' && str[i] != '-' \
			&& (str[i] < '0' || str[i] > '9'))
			return (false);
		++i;
	}
	return (true);
}

bool	ph_is_impair(size_t nbr)
{
	return (nbr % 2 != 0);
}
