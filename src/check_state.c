/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 06:06:04 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/19 01:43:18 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_check_if_philo_has_reached_meal_limit(t_env *env, int id)
{
	int	limit;

	limit = env->meal_limit;
	if (env->philo[id].meal_count == limit)
	{
		env->philo_reached_meal_limit = true;
		return (true);
	}
	return (false);
}

bool	ph_is_dead(t_env *env, int id)
{
	t_philo			*philo;
	struct timeval	tv;
	int				time_to_eat;

	philo = &env->philo[id];
	time_to_eat = env->time.eat;
	if (ph_gettime(env, &tv) == ERROR)
		return (true);
	if (philo->last_meal_time < (tv.tv_usec / 1000) - time_to_eat)
	{
		philo->is_dead = true;
		return (true);
	}
	return (false);
}

bool	ph_check_if_someone_died(t_env *env, bool print_msg)
{
	int	i;

	i = 0;
	while (i < env->philo_nbr)
	{
		if (ph_is_dead(env, i))
		{
			if (print_msg == true)
				printf("%i is dead", i + 1);
			env->philo_died = true;
			return (true);
		}
		++i;
	}
	return (false);
}
