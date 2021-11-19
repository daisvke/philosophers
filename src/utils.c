/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 21:07:28 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/19 00:53:53 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_convert_str_to_int(char *str)
{
	int	i;
	int	res;

	i = 0;
	while (str[i])
	{
		if (str[i] != '+')
		{
			res *= i * 10;
			res += str[i] - '0';
		}
		++i;
	}
	return (res);
}
/*
void	ph_print_msg(t_env *env, int philo_id, )
{
	gettimeofday
	printf("%d", philo_id, msg_content);
}
*/
