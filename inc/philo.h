/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:16:26 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/04 08:31:05 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

# define OK				0
# define SUCCESS		0
# define ERROR			1

# define ERR_LIMIT		11

# define RIGHT			-1
# define LEFT			0

# define MSG_TAKE_FORK  0
# define MSG_EATING     1
# define MSG_SLEEPING   2
# define MSG_THINKING   3
# define MSG_DEATH      4

# define MSG_COLOR_RED		"\033[0;31m"
# define MSG_COLOR_WHITE	"\033[0;37m"

typedef struct s_time
{
	size_t	start;
	size_t	current;
	size_t	die;
	size_t	eat;
	size_t	sleep;
}			t_time;

typedef struct s_env
{
	size_t			philo_nbr;
	t_time			time;
	size_t			meal_limit;
	size_t			curr_id;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	bool			philo_died;
	bool			philo_reached_meal_limit;
	bool			lock_print;
	bool			error_occured_on_some_thread;
	bool			errors[ERR_LIMIT];
}					t_env;

typedef struct s_philo
{
	size_t	id;
	t_env	*env;
	bool	monitor_on;
	size_t	last_meal_time;
	size_t	meal_count;
	bool	reached_meal_limit;	
}			t_philo;

/*
** system calls
*/
void	*ph_free(void *data);
void	*ph_malloc(t_env *env, size_t nbr, size_t size);

int	ph_convert_str_to_int(char *str);

void	*ph_start_routine(void *data);
#endif
