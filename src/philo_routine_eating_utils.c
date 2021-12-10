/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_eating_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 08:49:17 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/10 10:12:22 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_starve_if_solo_since_cannot_eat_with_one_fork(t_env *env, t_philo *philo)
{
	size_t	fork_id;

	fork_id = 0;
	if (ph_unlock_fork(env, fork_id) == ERROR \
		|| ph_usleep(env, env->time.die) == ERROR \
		|| ph_lock_philo_died(env) == ERROR)
		return (ERROR);
	env->philo_died = true;
	if (ph_unlock_philo_died(env) == ERROR \
		|| ph_print_msg(env, philo, MSG_DEATH) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	ph_get_forks_id(t_philo *philo, size_t *fork_ids)
{
	t_env	*env;
	size_t	philo_id;
	size_t	hold_first;
	size_t	hold_next;

	env = philo->env;
	philo_id = philo->id;
	fork_ids[FK_RIGHT] = philo_id - 1;
	if (philo_id == 0)
		fork_ids[FK_RIGHT] = env->philo_nbr - 1;
	fork_ids[FK_LEFT] = philo_id;
	philo_id = philo->id;
	if (ph_is_impair(philo_id) == true)
	{
		hold_first = fork_ids[FK_LEFT];
		hold_next = fork_ids[FK_RIGHT];
	}
	else
	{
		hold_first = fork_ids[FK_RIGHT];
		hold_next = fork_ids[FK_LEFT];
	}
	fork_ids[0] = hold_first;
	fork_ids[1] = hold_next;
}
