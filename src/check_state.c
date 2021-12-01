/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:06:04 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/21 11:33:10 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_check_if_philo_has_reached_meal_limit(t_env *env, t_philo *philo)
{
	size_t	limit;

	limit = env->meal_limit;
	if (limit && philo->meal_count == limit)
	{
		env->philo_reached_meal_limit = true;
		printf("reached limit\n");
		return (true);
	}
	return (false);
}

bool	ph_is_dead(t_env *env, t_philo *philo)
{
	size_t	time_to_eat;
	size_t	curr_time;
	size_t	time_diff;
	size_t	deadline_to_eat;
	size_t	last_meal_time;

	time_to_eat = env->time.eat;
	curr_time = 0;
	if (ph_gettime(env, &curr_time) == ERROR)
		return (true);
	time_diff = ph_get_diff_between_start_and_curr_time(env, curr_time);
	deadline_to_eat = (curr_time / 1000) - time_to_eat;
	last_meal_time = philo->last_meal_time / 1000;
printf("deadlineto_eat: %ld\n" , deadline_to_eat);
		printf("philo%d lastmealtime:%ld\n", philo->id, last_meal_time);
	if (deadline_to_eat > 0 && last_meal_time < deadline_to_eat)
	{
	printf("==+++++++++++++++===in is_dead\n");
		printf("philo%d lastmealtime:%ld\n", philo->id, last_meal_time);
		if (philo->monitor_on == true)
			printf("===>timediff:%ld\n", time_diff / 1000);
		philo->is_dead = true;
		return (true);
	}
	return (false);
}

bool	ph_check_if_philo_died(t_env *env, t_philo *philo)
{
	if (ph_is_dead(env, philo))
	{
		printf("philo%d is dead\n", philo->id);
		env->philo_died = true;
		return (true);
	}
	return (false);
}
