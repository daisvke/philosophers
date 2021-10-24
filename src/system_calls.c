/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_calls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 03:38:47 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/24 04:34:12 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_malloc(t_ppx *env, size_t nbr, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(nbr * size);
	if (!ptr)
	{
		env->errors[1] = true;
		return (NULL);
	}
	return (ptr);
}

void	*ph_free(void *data)
{
	if (data)
		free(data);
	return (NULL);
}

/*
int	ph_pthread_create()
		if (pthread_create( \
			&env->tid_array[i], NULL, ph_start_routine, env) \
			!= SUCCESS);
		{
			env->errors[2] = true;
*/
