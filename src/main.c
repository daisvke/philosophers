/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:16:24 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/10/21 18:34:22 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ph_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (false)
		++i;
	}
	return (true);
}

bool	ph_check_if_args_are_numbers(int argc, char *argv[])
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ph_is_number(argv[i]) == false)
			return (false);
		++i;
	}
	return (true);
}

bool	ph_check_args(int argc, char *argv[])
{
	if (argc < 5 || ph_check_if_args_are_numbers(argc, argv) == false)
		return (ERROR)
	return (OK);
}

int	ph_run_philosophers()
{
	
}

int	main(int argc, char *argv[])
{
	t_philosophers	env;

	if (ph_check_args(argc, argv) == OK)
	{
		ph_init_env(&env);
		ph_run_philosophers(&env);
		return (SUCCESS);
	}
	else
		return (ERROR);
}
