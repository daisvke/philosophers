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

char    **ph_get_msg_array(char **msg_arr)
{
    msg_arr[MSG_TAKE_FORK] = "has taken fork";
    msg_arr[MSG_EATING] = "is eating";
    msg_arr[MSG_SLEEPING] = "is sleeping";
    msg_arr[MSG_THINKING] = "is thinking";
    msg_arr[MSG_DEATH] = "is dead";
    return (msg_arr);
}

char	*ph_get_msg_content(size_t msg_code)
{
    char    *msg_arr[5];
    
    ph_get_msg_array(msg_arr);
    return (msg_arr[msg_code]);
}

int	ph_print_msg(t_env *env, t_philo *philo, size_t msg_code)
{
    size_t  curr_time;
	char	*msg_content;

	msg_content = ph_get_msg_content(msg_code);
    if (env->philo_died == false || msg_code == MSG_DEATH)
    {
        if (ph_gettime(env, &curr_time) == ERROR)
            return (ERROR);
        printf("%ld %d %s\n", curr_time, philo->id, msg_content);
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
