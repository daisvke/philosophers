/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros_and_structs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 04:18:11 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/01/06 04:09:31 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_AND_STRUCTS_H
# define MACROS_AND_STRUCTS_H

// RETURNS
# define OK					0

enum e_return
{
	SUCCESS,
	ERROR
};

# define LIFE_MONITOR		1
# define ERR_LIMIT			17

// FORK SIDES
enum e_forks
{
	FK_RIGHT,
	FK_LEFT
};

// MESSAGES
# define MSG_COLOR_RED		"\033[0;31m"
# define MSG_COLOR_GREEN	"\033[0;32m"
# define MSG_COLOR_WHITE	"\033[0;37m"

enum e_messages
{
	MSG_TAKE_FORK,
	MSG_EATING,
	MSG_SLEEPING,
	MSG_THINKING,
	MSG_DEATH
};

// LOCKS
# define LOCK_NBR			7

enum e_locks
{
	LK_LOCK_PRINT,
	LK_PHILO_DIED,
	LK_LAST_MEAL_TIME,
	LK_START_SIMULATION,
	LK_REACHED_MEAL_LIMIT,
	LK_PRINTF,
	LK_CREATE_THREAD
};

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
	bool			first_turn;
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

#endif
