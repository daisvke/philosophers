/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_center.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 08:06:12 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/04 08:33:03 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	size_t	philo_id;

	msg_content = ph_get_msg_content(msg_code);
    if (env->lock_print == false
		&& ((env->philo_died == false 
		&& philo->reached_meal_limit == false
		&& env->error_occured_on_some_thread == false)
		|| msg_code == MSG_DEATH))
    {
		if (msg_code == MSG_DEATH)
			ph_lock_death_msg_when_someone_already_died(env);
		if (ph_get_diff_between_start_and_curr_time(env, &timestamp) == ERROR)
            return (ERROR);
		timestamp_in_ms = timestamp / 1000;
		philo_id = philo->id + 1;
		if (msg_code == MSG_DEATH)
			printf("%s", MSG_COLOR_RED);
        printf("%ld %ld %s\n", timestamp_in_ms, philo_id, msg_content);
		if (msg_code == MSG_DEATH)
			printf("%s", MSG_COLOR_WHITE);
    }
	return (SUCCESS);
}
