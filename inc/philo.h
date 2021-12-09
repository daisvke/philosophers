/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:16:26 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/12/09 23:58:38 by root             ###   ########.fr       */
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

# define OK					0
# define SUCCESS			0
# define ERROR				1

# define LIFE_MONITOR		1
# define ERR_LIMIT			12

// FORK SIDES
# define FK_RIGHT			0
# define FK_LEFT			1

// MESSAGES
# define MSG_TAKE_FORK  	0
# define MSG_EATING     	1
# define MSG_SLEEPING   	2
# define MSG_THINKING   	3
# define MSG_DEATH      	4

# define MSG_COLOR_RED		"\033[0;31m"
# define MSG_COLOR_WHITE	"\033[0;37m"

// LOCKS
# define LOCK_NBR				11

# define LK_LOCK_PRINT			0
# define LK_PHILO_DIED			1
# define LK_LAST_MEAL_TIME		2
# define LK_START_SIMULATION	3
# define LK_ERRORS				4
# define LK_FREE				5
# define LK_REACHED_MEAL_LIMIT	6
# define LK_END_CONDITIONS		7
# define LK_PRINTF				8
# define LK_CREATE_THREAD		9
# define LK_JOIN_THREAD			10

// TIME & DURATIONS
typedef struct s_time
{
	size_t	start;
	size_t	die;
	size_t	eat;
	size_t	sleep;
}			t_time;

// MAIN STRUCTURE
typedef struct s_env
{
	size_t			philo_nbr;
	t_time			time;
	size_t			meal_limit;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	locks[LOCK_NBR];
	bool			lock_print;
	bool			philo_died;
	bool			philo_reached_meal_limit;
	bool			error_occured_on_some_thread;
	bool			errors[ERR_LIMIT];
}					t_env;

// FOR EACH PHILOSOPHER
typedef struct s_philo
{
	size_t	id;
	t_env	*env;
	bool	start_simulation;
	size_t	last_meal_time;
	size_t	meal_count;
	bool	reached_meal_limit;	
}			t_philo;

/*
** system calls
*/
void	*ph_malloc(t_env *env, size_t nbr, size_t size);
void	*ph_free(void *data);
int		ph_usleep(t_env *env, size_t msec);
int		ph_gettime(t_env *env, size_t *curr_time);
size_t	ph_strlen(const char *s);
int		ph_pthread_mutex_init(t_env *env, pthread_mutex_t *mutex);
int		ph_pthread_create(t_env *env, pthread_t *tid, void *(f)(void *), \
	t_philo *philo);
int		ph_pthread_join(t_env *env, pthread_t tid);
int		ph_pthread_mutex_lock(t_env *env, pthread_mutex_t *mutex);
int		ph_pthread_mutex_unlock(t_env *env, pthread_mutex_t *mutex);

/*
** init struct
*/
void	ph_init_errors(t_env *env);
int		ph_init_env(t_env *env, int argc, char *argv[], t_philo **philo_arr);

/*
** messages
*/
int		ph_print_msg(t_env *env, t_philo *philo, size_t msg_code);
int		ph_print_errors_if_any_and_exit(t_env env);

/*
** monitor
*/
int		ph_run_life_monitor(t_philo *philo, pthread_t *monitor_tid);
bool	ph_check_if_philo_has_reached_meal_limit(t_env *env, t_philo *philo);
bool	ph_is_dead(t_env *env, t_philo *philo);

/*
** philo
*/
void	ph_run_philo(t_env *env, t_philo *philo_arr);
void	*ph_start_routine(void *data);
int		ph_is_eating(t_env *env, t_philo *philo);

/*
** utils
*/
int		ph_convert_str_to_int(char *str);
int		ph_get_diff_between_start_and_curr_time(t_env *env, size_t *time_diff);
void	ph_put_nbr_to_stderr(size_t nbr);
bool	ph_is_numeric(char *str);
bool	ph_is_impair(size_t nbr);

/*
** exit
*/
void	ph_clean_arrays(t_env *env, t_philo *philo_arr);

#endif
