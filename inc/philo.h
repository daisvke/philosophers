/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:16:26 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/10 01:06:55 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <bool.h>
# include <pthread.h>
# include <stdio.h>

# define OK			0
# define SUCCESS	0
# define ERROR		1

# define ERR_LIMIT	3

typedef struct s_time
{
	int	die;
	int	eat;
	int	sleep;
}		t_time;

typedef struct s_philo
{
	int		id;
	bool	dead;
	t_time	time;
	int		last_meal_time;
}			t_philo;

typedef struct s_env
{
	int				philo_nbr;
	t_time			time;
	int				eat_limit;
	t_philo			*philo;
	pthread_t		*threads
	pthread_mutex_t	*forks;
	bool			errors[ERR_LIMIT];
}					t_env;

/*
** system calls
*/
void	*ph_malloc(t_ppx *env, size_t nbr, size_t size);

int	ph_convert_str_to_int(char *str);

#endif
