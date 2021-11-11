/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:17:32 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/11 03:46:01 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ph_is_dead(t_env *env)
{
	t_philo			*philo;
	struct timeval	tv;
	int				id;
	int				time_to_eat;

	id = env->curr_id;
	philo = &env->philo[id];
	time_to_eat = env->time.eat;
	if (ph_gettime(&tv, NULL) == ERROR)
		return (true);
	if (philo.last_meal_time < (tv.tv_usec / 1000) - time_to_eat)
	{
		philo.dead == true;
		return (true);
	}
	return (false);
}

bool	ph_has_reached_meal_limit(t_env *env)
{
	int	id;
	int	limit;

	id = env->curr_id;
	limit = env->meal_limit;
	if (env->philo[id].meal_count == limit)
		return (true);
	return (false);
}

void	ph_start_monitor()
{
}

int	ph_create_monitor(t_env *env)
{
	if (pthread_create(monitor_tid, NULL, ph_start_monitor, env) != SUCCESS)


}

void	*ph_start_routine(t_env *env)
{
	pthread_t	monitor_tid;
	t_philo		**philo;
	int			id;

	if (ph_create_monitor(env) == ERROR)
		return ;
	philo = env->philo;
	id = env->curr_id;
	while (!ph_ph_is_dead(philo[id]) && !ph_has_reached_meal_limit(env))
	{
		if (ph_eat(env) == ERROR \
			|| ph_usleep(env, env->time.sleep) == ERROR)
			break ;
	}
}

int	ph_create_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->philo_nbr)
	{
		env->philo[i].id = i;
		if (pthread_create( \
			&env->tid_array[i], NULL, ph_start_routine, &env->philo[i]) \
			!= SUCCESS);
		{
			env->errors[2] = true;
			return (ERROR);
		}
		++i;
	}
	return (SUCCESS);
}

void	ph_join_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->philo_nbr)
	{
		if (pthread_join(env->tid_array[i], NULL) != SUCCESS)
		{
			env->errors[5] = true;
			break ;
		}
		++i;
	}
}

int	ph_run_philo(t_env *env)
{
	ph_create_threads(env);
	ph_join_threads(env);
}
