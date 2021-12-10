/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message_center.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 08:06:12 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/10 10:09:32 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	**ph_get_msg_array(char **msg_arr)
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
	char	*msg_arr[5];

	ph_get_msg_array(msg_arr);
	return (msg_arr[msg_code]);
}

int	ph_lock_death_msg_when_someone_already_died(t_env *env)
{
	if (ph_lock_print(env) == ERROR)
		return (ERROR);
	env->lock_print = true;
	if (ph_unlock_print(env) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_put_msg_on_terminal(t_philo *philo, size_t msg_code, char *msg_content)
{
	t_env	*env;
	size_t	philo_id;
	size_t	timestamp;
	size_t	timestamp_in_ms;

	env = philo->env;
	if (msg_code == MSG_DEATH)
		ph_lock_death_msg_when_someone_already_died(env);
	if (ph_get_diff_between_start_and_curr_time(env, &timestamp) == ERROR)
		return (ERROR);
	timestamp_in_ms = timestamp / 1000;
	philo_id = philo->id + 1;
	if (ph_lock_printf(env) == ERROR)
		return (ERROR);
	if (msg_code == MSG_DEATH)
		printf("%s", MSG_COLOR_RED);
	else if (ph_is_impair(philo_id) == true)
		printf("%s", MSG_COLOR_GREEN);
	printf("%3ld\t%3ld\t%s\n", timestamp_in_ms, philo_id, msg_content);
	printf("%s", MSG_COLOR_WHITE);
	return (SUCCESS);
}

int	ph_print_msg(t_env *env, t_philo *philo, size_t msg_code)
{
	char	*msg_content;

	if (ph_lock_print(env) == ERROR)
		return (ERROR);
	msg_content = ph_get_msg_content(msg_code);
	if (env->lock_print == false \
		&& (ph_continue_diner(env, philo) == true || msg_code == MSG_DEATH))
	{
		if (ph_unlock_print(env) == ERROR \
			|| ph_put_msg_on_terminal(philo, msg_code, msg_content) == ERROR \
			|| ph_unlock_printf(env) == ERROR)
			return (ERROR);
	}
	else
	{	
		if (ph_unlock_print(env) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}
