/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:07:28 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/20 21:55:14 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_convert_str_to_int(char *str)
{
	int	i;
	int	res;

	i = 0;
	while (str[i])
	{
		if (str[i] != '+')
		{
			res *= i * 10;
			res += str[i] - '0';
		}
		++i;
	}
	return (res);
}
/*
void	ph_print_msg(t_env *env, int philo_id, )
{
	gettimeofday
	printf("%d", philo_id, msg_content);
}
*/

size_t	ph_get_diff_between_start_and_curr_time(t_env *env, size_t curr_time)
{
	size_t	start_time;
	size_t	time_diff;
	pthread_mutex_t	mutex;

	start_time = env->time.start;
	time_diff = curr_time - start_time;
	return (time_diff);
}
