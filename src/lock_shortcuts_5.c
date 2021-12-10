/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock_shortcuts_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:20:55 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/10 10:21:46 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_lock_conditions(t_env *env)
{
	if (ph_lock_reached_meal_limit(env) == ERROR \
		|| ph_lock_philo_died(env) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_conditions(t_env *env)
{
	if (ph_unlock_philo_died(env) == ERROR \
		|| ph_unlock_reached_meal_limit(env) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_lock_conditions_2(t_env *env)
{
	if (ph_lock_philo_died(env) == ERROR \
		|| ph_lock_reached_meal_limit(env) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_unlock_conditions_2(t_env *env)
{
	if (ph_unlock_reached_meal_limit(env) == ERROR \
		|| ph_unlock_philo_died(env) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
