

#include "philo.h"

int	ph_pthread_mutex_init(t_env *env, pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != SUCCESS)
	{
		env->errors[9] = true;
		return (ERROR);
	}
	return (SUCCESS);
} 

int	ph_pthread_create(t_env *env, pthread_t *tid, void *(f)(void *), t_philo *philo)
{
	if (pthread_create( \
		tid, NULL, (f), philo) != SUCCESS)
	{
		env->errors[2] = true;
		return (ERROR);
	}
	return (SUCCESS);
}
