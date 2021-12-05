/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:57:32 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/04 08:09:41 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	**ph_get_array_of_error_messages(char *errors[])
{
	errors[0] = "Usage: ./philo [number of philosophers] [time to die]" \
		" [time to eat] [time to sleep]" \
		" [number of times each philosopher must eat] (optionnal)";
	errors[1] = "Malloc failed";
	errors[2] = "Failed to create new thread";
	errors[3] = "Failed to lock mutex";
	errors[4] = "Failed to unlock mutex";
	errors[5] = "Failed to join thread";
	errors[6] = "usleep failed";
	errors[7] = "gettimeofday failed";
	errors[8] = "arguments should be numbers";
	errors[9] = "failed to init mutex";
	return (errors);
}

char	*ph_get_err_message_from_err_code(size_t err_code)
{
	char	*err_messages[ERR_LIMIT + 1];

	ph_get_array_of_error_messages(err_messages);
	return (err_messages[err_code]);
}

void	ph_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ph_strlen(s));
}

void	ph_print_error_message(t_env env, size_t err_code)
{
	char	*err_message;

	err_message = NULL;
	err_message = ph_get_err_message_from_err_code(err_code);
	ph_putstr_fd("ERROR CODE ", STDERR_FILENO);
	ph_put_nbr_to_stderr(err_code);
	ph_putstr_fd("\n", STDERR_FILENO);
	ph_putstr_fd(MSG_COLOR_RED, STDERR_FILENO);
	ph_putstr_fd(err_message, STDERR_FILENO);
	ph_putstr_fd(MSG_COLOR_WHITE, STDERR_FILENO);
	ph_putstr_fd("\n", STDERR_FILENO);
}

int	ph_print_errors_and_exit(t_env env)
{
	size_t	err_code;
	bool	found_error;
	bool	already_printed;

	err_code = 0;
	found_error = false;
	already_printed = false;
	while (err_code < ERR_LIMIT)
	{
		if (env.errors[err_code] == true)
		{
			if (already_printed == false)
			{
				ph_putstr_fd("philo:\n", STDERR_FILENO);
				already_printed = true;
			}
			ph_print_error_message(env, err_code);
			found_error = true;
		}
		++err_code;
	}
	ph_putstr_fd("\n", STDERR_FILENO);
	if (found_error == true)
		return (ERROR);
	return (OK);
}

int	ph_return_and_alert_error(t_env *env)
{
	env->error_occured_on_some_thread = true;
	return (ERROR);
}
