/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtanigaw <dtanigaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 08:18:20 by dtanigaw          #+#    #+#             */
/*   Updated: 2021/11/29 08:35:11 by dtanigaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "inc/philo.h"

typedef struct s_envv
{
	size_t id;
	pthread_mutex_t *forks;
	pthread_t *tid;
    pthread_mutex_t c;
	size_t n;
	size_t p;
}		t_envv;

typedef struct s_ph
{
    size_t id;
    t_envv   *envv;
}		t_ph;

void	*f(t_ph *ph)
{
	size_t	id;
	id = ph->id;
	printf("n in f: %ld, i = %ld\n", ph->envv->n, ph->envv->id);

//pthread_mutex_lock(&envv->c);
	if (ph->id >0)
		ph->id = ph->id - 1;
	else
		ph->id = ph->envv->n;
	pthread_mutex_lock(&ph->envv->forks[id]);
//pthread_mutex_unlock(&envv->c);
	printf("this is the unlocked message from fork n.: %d\n", ph->id);
	pthread_mutex_unlock(&ph->envv->forks[id]);
	return (NULL);
}

void	init(t_envv *envv)
{

		printf("in init : n: %d\n",envv->n);
	envv->forks = malloc(envv->n * sizeof(pthread_mutex_t));
  	size_t i;
    pthread_mutex_init(&envv->c,NULL);
    for(i=0;i<envv->n;i++)
        pthread_mutex_init(&envv->forks[i],NULL);
envv->tid = malloc(envv->n * sizeof(pthread_t));
}

int main()
{
	static t_envv	envv;
	size_t i =0;
	envv.n = 3;
    t_ph *ph;
    ph = malloc(envv.n * sizeof(t_ph));
	init(&envv);
	for (i=0;i < envv.n;i++)
	{
		printf("i: %d, n: %d\n", i, envv.n);
	   ph[i].id = i;
       ph[i].envv=&envv;
		pthread_create(&envv.tid[i], NULL, (void*)f, &ph[i]);
		printf("thread no %d created\n", i);
	}
	for (i=0;i<envv.n;i++)
	{
		pthread_join(envv.tid[i], NULL);
		printf("thread no %d joined\n", i);
	}
}

