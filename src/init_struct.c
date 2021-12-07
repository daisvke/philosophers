/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:35:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/07 10:44:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_init_errors(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < ERR_LIMIT)
		env->errors[i++] = false;
}

int	ph_init_tid_array(t_env *env)
{
	size_t	philo_nbr;

	philo_nbr = env->philo_nbr;
	env->threads = (pthread_t *)ph_malloc(env, philo_nbr, sizeof(pthread_t));
	if (!env->threads)
		return (ERROR);
	return (SUCCESS);
}

int	ph_init_fork_array(t_env *env)
{
	size_t	philo_nbr;
	size_t	i;

	philo_nbr = env->philo_nbr;
	env->forks = (pthread_mutex_t *)ph_malloc(\
		env, philo_nbr, sizeof(pthread_mutex_t));
	if (!env->forks)
		return (ERROR);
	i = 0;
	while (i < philo_nbr)
	{
		if (ph_pthread_mutex_init(env, &env->forks[i]) == ERROR)
			return (ERROR);
		++i;
	}
	return (SUCCESS);
}

int	ph_init_philo_array(t_env *env, t_philo **philo_arr)
{
	size_t	philo_nbr;
	size_t	i;

	philo_nbr = env->philo_nbr;
	*philo_arr = (t_philo *)ph_malloc(env, philo_nbr, sizeof(t_philo));
	if (!*philo_arr)
		return (ERROR);
	i = 0;
	while (i < philo_nbr)
	{
		memset(&(*philo_arr)[i], 0, sizeof(t_philo));
		(*philo_arr)[i].env = env;
		++i;
	}
	return (SUCCESS);
}

int	ph_init_lock_array(t_env *env)
{
	size_t	i;

	i = 0;
	while (i < LOCK_NBR)
	{
		if (ph_pthread_mutex_init(env, &env->locks[i]) == ERROR)
			return (ERROR);
		++i;
	}
	return (SUCCESS);
}
	
int	ph_init_env(t_env *env, int argc, char *argv[], t_philo **philo_arr)
{
	memset(env, 0, sizeof(t_env));
	env->philo_nbr = ph_convert_str_to_int(argv[1]);
	env->time.die = ph_convert_str_to_int(argv[2]);
	env->time.eat = ph_convert_str_to_int(argv[3]);
	env->time.sleep = ph_convert_str_to_int(argv[4]);
	if (argc > 5)
		env->meal_limit = ph_convert_str_to_int(argv[5]);
	if (ph_init_tid_array(env) == ERROR \
		|| ph_init_fork_array(env) == ERROR \
		|| ph_init_lock_array(env) == ERROR \
		|| ph_init_philo_array(env, philo_arr) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
