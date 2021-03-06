/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:16:26 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/01/06 04:17:09 by dtanigaw         ###   ########.fr       */
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

# include "macros_and_structs.h"

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
** check arguments
*/
bool	ph_check_args(t_env *env, int argc, char *argv[]);

/*
** init struct
*/
int		ph_init_env(t_env *env, t_philo **philo_arr);

/*
** lock shortcuts
*/
int		ph_lock_fork(t_env *env, size_t id);
int		ph_unlock_fork(t_env *env, size_t id);
int		ph_lock_print(t_env *env);
int		ph_unlock_print(t_env *env);
int		ph_lock_philo_died(t_env *env);
int		ph_unlock_philo_died(t_env *env);
int		ph_lock_last_meal_time(t_env *env);
int		ph_unlock_last_meal_time(t_env *env);
int		ph_lock_start_simulation(t_env *env);
int		ph_unlock_start_simulation(t_env *env);
int		ph_lock_reached_meal_limit(t_env *env);
int		ph_unlock_reached_meal_limit(t_env *env);
int		ph_lock_printf(t_env *env);
int		ph_unlock_printf(t_env *env);
int		ph_lock_create_thread(t_env *env);
int		ph_unlock_create_thread(t_env *env);
int		ph_lock_conditions(t_env *env);
int		ph_unlock_conditions(t_env *env);
int		ph_lock_conditions_2(t_env *env);
int		ph_unlock_conditions_2(t_env *env);

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
void	*ph_start_routine_philo(void *data);
bool	ph_continue_diner(t_env *env, t_philo *philo);
int		ph_is_eating(t_env *env, t_philo *philo);
int		ph_starve_if_solo_since_cannot_eat_with_one_fork(\
	t_env *env, t_philo *philo);
void	ph_get_forks_id(t_philo *philo, size_t *fork_ids);

/*
** utils
*/
size_t	ph_convert_str_to_int(t_env *env, char *str, bool *error);
int		ph_get_diff_between_start_and_curr_time(t_env *env, size_t *time_diff);
void	ph_put_nbr_to_stderr(size_t nbr);
bool	ph_is_numeric(char *str);
bool	ph_is_impair(size_t nbr);

/*
** exit
*/
void	ph_clean_arrays(t_env *env, t_philo *philo_arr);

#endif
