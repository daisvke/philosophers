/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:35:35 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/29 08:13:02 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_init_errors(t_env *env)
{
	int	i;

	i = 0;
	while (i < ERR_LIMIT)
		env->errors[i++] = false;
}

int	ph_init_tid_array(t_env *env)
{
	int	philo_nbr;

	philo_nbr = env->philo_nbr;
	env->threads = (pthread_t *)ph_malloc(env, philo_nbr, sizeof(pthread_t));
	if (!env->threads)
		return (ERROR);
	return (SUCCESS);
}

int	ph_init_fork_array(t_env *env)
{
	int	philo_nbr;
	int	i;

	philo_nbr = env->philo_nbr;
	env->forks = (pthread_mutex_t *)ph_malloc( \
		env, philo_nbr, sizeof(pthread_mutex_t));
	if (!env->forks)
		return (ERROR);
	i = 0;
	while (i < philo_nbr)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) != SUCCESS)
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
		(*philo_arr)[i].id = 0;
		(*philo_arr)[i].is_dead = false;
		(*philo_arr)[i].env = env;
		(*philo_arr)[i].meal_count = 0;
		++i;
	}
	return (SUCCESS);
}

int	ph_init_env(t_env *env, int argc, char *argv[], t_philo *philo_arr)
{
	pthread_t	tid;

	memset(env, 0, sizeof(t_env));
	env->philo_nbr = ph_convert_str_to_int(argv[1]);
	env->time.die = ph_convert_str_to_int(argv[2]);
	env->time.eat = ph_convert_str_to_int(argv[3]);
	env->time.sleep = ph_convert_str_to_int(argv[4]);
	env->monitor_tid = tid;
	if (pthread_mutex_init(&env->mutex, NULL) != SUCCESS)
		return (ERROR);
	if (argc > 5)
		env->meal_limit = ph_convert_str_to_int(argv[5]);
	if (ph_init_tid_array(env) == ERROR \
		|| ph_init_fork_array(env) == ERROR \
		|| ph_init_philo_array(env, &philo_arr) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
