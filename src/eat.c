/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 05:46:03 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/29 08:36:08 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_hold_fork(t_env *env, int side, int philo_id)
{
	int	fork_id;
	size_t	t;
	size_t	curr_time;

	if (env->philo_died == false)
	{
		fork_id = philo_id + side;
		printf("philo_died is false\n");
		if (pthread_mutex_lock(&env->forks[fork_id]) != SUCCESS)
		{
			printf("lock error fork\n");
			env->errors[3] = true;
			return (ERROR);
		}
//pthread_mutex_lock(&env->mutex);
		fork_id = philo_id + side;
		if (philo_id == 0 && side == RIGHT)
			fork_id = env->philo_nbr - 1;
//pthread_mutex_unlock(&env->mutex);
	if (ph_gettime(env, &curr_time) == ERROR)
		return (true);
	t = ph_gettimediff(env, curr_time);
		printf("%ld id : %d, fork_id:%d\n", t/1000, philo_id, fork_id);
		printf("%d has taken a fork\n", philo_id);
	}
	return (SUCCESS);
}

int	ph_drop_forks(t_env *env, int philo_id)
{
	int	r_fork;
	int	l_fork;

	if (env->philo_died == false)
	{
		r_fork = philo_id - 1;
		if (philo_id == 0)
			r_fork = env->philo_nbr - 1;
		l_fork = philo_id;
		if (pthread_mutex_unlock(&env->forks[r_fork]) != SUCCESS \
			|| pthread_mutex_unlock(&env->forks[l_fork]) != SUCCESS)
		{
			env->errors[4] = true;
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	ph_wait_until_eating(t_env *env, int philo_id)
{
	printf("%d is eating\n", philo_id);
	if (ph_usleep(env, env->time.eat) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ph_eat(t_env *env, t_philo *philo)
{
	size_t	philo_id;

	philo_id = philo->id;
	if (ph_hold_fork(env, RIGHT, philo_id) == ERROR \
		|| ph_hold_fork(env, LEFT, philo_id) == ERROR \
		|| ph_wait_until_eating(env, philo_id) == ERROR \
		|| ph_drop_forks(env, philo_id) == ERROR)
	{
		printf("thats an error\n");
		return (ERROR);
	}
	++philo->meal_count;
	ph_check_if_philo_has_reached_meal_limit(env, philo_id);
	return (SUCCESS);
}
