/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 03:38:47 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/04 05:28:41 by dtanigaw         ###   ########.fr       */
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

int	ph_usleep(t_env *env, size_t msec)
{
	if (usleep(msec * 1000) != SUCCESS)
	{
		env->error_occured_on_some_thread = true;
		env->errors[6] = true;
		return (ERROR);
	}
	return (SUCCESS);
}

int	ph_gettime(t_env *env, size_t *curr_time)
{
	struct timeval	tv;
	size_t			sec_in_usec;
	size_t			usec;
	
	if (gettimeofday(&tv, NULL) != SUCCESS)
	{
		env->error_occured_on_some_thread = true;
		env->errors[7] = true;
		return  (ERROR);
	}
	sec_in_usec = tv.tv_sec * 1000000;
	usec = tv.tv_usec;
	*curr_time = sec_in_usec + usec;
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
