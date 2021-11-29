/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:17:32 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/29 08:10:00 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_join_threads(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->philo_nbr)
	{
		if (pthread_join(env->threads[i], NULL) != SUCCESS)
		{
			env->errors[5] = true;
			break ;
		}
		++i;
	}
	if (pthread_join(env->monitor_tid, NULL) != SUCCESS)
		env->errors[5] = true;
}

bool	ph_continue_diner(t_env *env)
{
	if (ph_check_if_someone_died(env, false) == false
		&& env->philo_reached_meal_limit == false)
		return (true);
	printf("continue diner == false\n");
	return (false);
}

void	*ph_start_routine(void *data)
{
	t_env	**env;
	t_philo	*philo;
	size_t	id;

	env = philo->env;
	philo = (t_philo *)data;
	id = philo->id;
	philo->env->monitor_on = true;
	printf("start routine for id: %d\n", id);
	while (ph_continue_diner(env) == true)
	{
		if (ph_eat(env, philo) == ERROR \
			|| ph_usleep(env, env->time.sleep, id) == ERROR)
		{
			printf("eat or usleep == error\n");
			break ;
		}
	}
	return (NULL);
}

int	ph_init_start_time(t_env *env)
{
	size_t		start_time;

	if (ph_gettime(env, &start_time) == ERROR)
		return (ERROR);
	env->time.start = start_time;
	printf("starttime : %ld\n", start_time);
	return (SUCCESS);
}

int	ph_spawn_philosophers(t_env *env, t_philo *philo_arr)
{
	size_t	i;

	if (ph_init_start_time(env) == ERROR)
		return (ERROR);
	i = 0;
	while (i < env->philo_nbr)
	{
	printf("create thread for id : %d\n", i);
		philo[i].id = i;
		if (ph_pthread_create( \
			env, &env->threads[i], ph_start_routine, &philo_arr[i]) != SUCCESS)
		{
			env->errors[2] = true;
			return (ERROR);
		}
		++i;
	}
	return (SUCCESS);
}

int	ph_run_philo(t_env *env, t_philo *philo_arr)
{
	if (ph_run_life_monitor(env) == ERROR \
		|| ph_spawn_philosophers(env, philo_arr) == ERROR)
		return (ERROR);
	ph_join_threads(env);
	return (SUCCESS);
}
