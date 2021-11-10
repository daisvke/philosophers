/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:16:26 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/10 06:23:32 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <bool.h>
# include <pthread.h>
# include <stdio.h>

# define OK				0
# define SUCCESS		0
# define ERROR			1

# define ERR_LIMIT		3

# define RIGHT			-1
# define LEFT			1

typedef struct s_time
{
	int	die;
	int	eat;
	int	sleep;
}		t_time;

typedef struct s_philo
{
	bool	dead;
	int		last_meal_time;
	int		meal_count;
}			t_philo;

typedef struct s_env
{
	int				philo_nbr;
	t_time			time;
	int				meal_limit;
	int				curr_id;
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
