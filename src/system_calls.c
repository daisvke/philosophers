/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 03:38:47 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/26 04:13:47 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_malloc(t_env *env, size_t nbr, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(nbr * size);
	if (!ptr)
		env->errors[1] = true;
	return (ptr);
}

void	*ph_free(void *data)
{
	if (data)
		free(data);
	return (NULL);
}

/*
long    get_timestamp(long start_ts)
{
    struct timeval    tv;

    gettimeofday(&tv, NULL);
    return (((tv.tv_sec * 1000) + tv.tv_usec / 1000) - start_ts);
}

void ft_usleep(int duration)
{
    long start;
    long current;

    start = get_timestamp(0);
    current = start;
    while (duration > current - start)
    {
        usleep(100);
        current = get_timestamp(0);
    }
}
*/

int	ph_usleep(t_env *env, size_t msec)
{
	if (usleep(msec * 1000) != SUCCESS)
	{
		env->errors[6] = true;
		return (ERROR);
	}
	return (SUCCESS);
}

int	ph_gettime(t_env *env, size_t *curr_time)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL) != SUCCESS)
	{
		env->errors[7] = true;
		return  (ERROR);
	}
	*curr_time = tv.tv_usec;
	return (SUCCESS);
}

int	ph_pthread_create(t_env *env, pthread_t *tid, void *(f)(void *))
{
	if (pthread_create( \
		tid, NULL, (f), env) != SUCCESS)
	{
		env->errors[2] = true;
		return (ERROR);
	}
	return (SUCCESS);
}

size_t	ph_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
