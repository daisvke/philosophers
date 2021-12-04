/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:07:28 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/04 04:51:15 by dtanigaw         ###   ########.fr       */
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

char    **ph_get_msg_array(char **msg_arr)
{
    msg_arr[MSG_TAKE_FORK] = "has taken a fork";
    msg_arr[MSG_EATING] = "is eating";
    msg_arr[MSG_SLEEPING] = "is sleeping";
    msg_arr[MSG_THINKING] = "is thinking";
    msg_arr[MSG_DEATH] = "died";
    return (msg_arr);
}

char	*ph_get_msg_content(size_t msg_code)
{
    char    *msg_arr[5];
    
    ph_get_msg_array(msg_arr);
    return (msg_arr[msg_code]);
}

void	ph_lock_death_msg_when_someone_already_died(t_env *env)
{
	env->lock_print = true;
}

int	ph_print_msg(t_env *env, t_philo *philo, size_t msg_code)
{
	char	*msg_content;
    size_t  timestamp;
	size_t	timestamp_in_ms;

	msg_content = ph_get_msg_content(msg_code);
    if (env->lock_print == false
		&& (env->philo_died == false || msg_code == MSG_DEATH))
    {
		if (msg_code == MSG_DEATH)
			ph_lock_death_msg_when_someone_already_died(env);
		if (ph_get_diff_between_start_and_curr_time(env, &timestamp) == ERROR)
            return (ERROR);
		timestamp_in_ms = timestamp / 1000;
        printf("%ld %ld %s\n", timestamp_in_ms, philo->id, msg_content);
    }
	return (SUCCESS);
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
