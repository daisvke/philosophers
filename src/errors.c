/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:57:32 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/10 05:44:45 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	**ph_get_array_of_error_messages(char *errors[])
{
	errors[0] = "\nUsage: ./philo [number of philosophers] [time to die] \
		[time to eat] [time to sleep] \
		[number of times each philosopher must eat] (optionnal)\n";
	errors[1] = "malloc failed";
	errors[2] = "failed to create new thread";
	errors[3] = "failed to lock mutex";
	errors[4] = "failed to unlock mutex";
	errors[5] = "failed to join thread";
	errors[6] = "usleep failed";
	return (errors);
}

char	*ph_get_err_message_from_err_code(int err_code)
{
	char	*err_messages[ERR_LIMIT + 1];

	ph_get_array_of_error_messages(err_messages);
	return (err_messages[err_code]);
}

void	ph_exit_with_error_message(t_ppx *env, int err_code)
{
	char	*err_message;

	err_message = NULL;
	err_message = ph_get_err_message_from_err_code(err_code);
	ph_putstr_fd("philo: ", STDERR_FILENO, NONE);
	ph_putstr_fd(err_message, STDERR_FILENO, NEWLINE);
}

int	ph_check_errors(t_env *env)
{
	int		i;

	i = 0;
	while (i <= ERR_LIMIT)
	{
		if (env->errors[i] == true)
		{
			sl_print_err_message(i);
			return (ERROR);
		}
		++i;
	}
	return (OK);
}
