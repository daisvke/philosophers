/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:07:28 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/01 17:00:36 by dtanigaw         ###   ########.fr       */
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


	ph_get_msg_content(msg_code);

int	ph_print_msg(t_env *env, t_philo *philo, size_t msg_code)
{
    size_t  curr_time;
	char	*msg_content;

	ph_get_msg_content(msg_code);
    if (env->philo_died == false)
    {
        if (ph_gettime(env, &curr_time) == ERROR)
            return (ERROR);
        printf("%ld %d %s", philo->id, msg_content);
    }
	return (SUCCESS);
}

size_t	ph_get_diff_between_start_and_curr_time(t_env *env, size_t curr_time)
{
	size_t	start_time;
	size_t	time_diff;
	pthread_mutex_t	mutex;

	start_time = env->time.start;
	time_diff = curr_time - start_time;
	return (time_diff);
}
