/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:07:28 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/01/06 03:58:28 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ph_convert_str_to_int(t_env *env, char *str, bool *error)
{
	size_t		i;
	long long	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (i != 0)
			res *= 10;
		res += str[i] - '0';
		++i;
	}
	if (res > 2147483647)
	{
		env->errors[15] = true;
		*error = true;
	}
	else if (res == 0)
	{
		env->errors[16] = true;
		*error = true;
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
