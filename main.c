#include "inc/philo.h"

typedef struct s_envv
{
	size_t id;
	pthread_mutex_t *forks;
	pthread_t *tid;
	size_t n;
	size_t p;
}		t_envv;

void	*f(t_envv *envv)
{
	size_t	id = envv->id;
	printf("n in f: %ld, i = %ld\n", envv->n, envv->id);

	if (id >0)
		id = id - 1;
	else
		id = envv->n;
	pthread_mutex_lock(&envv->forks[id]);
	printf("this is the unlocked message from id: %d\n", id);
	pthread_mutex_unlock(&envv->forks[id]);
}

void	init(t_envv *envv)
{
		printf("in init : n: %d\n",envv->n);
	envv->forks = malloc(envv->n * sizeof(pthread_mutex_t));
	envv->tid = malloc(envv->n * sizeof(pthread_t));
}
/*

int main()
{
	t_envv	*envv;
	size_t i =0;

	envv=malloc(sizeof(t_envv));

	envv->n = 3;
	envv->p = 5;
	init(envv);
		printf("before : p: %d\n",envv->p);

printf("before : n: %d\n",envv->n);
envv->n = 3;
for (i=0;i < envv->n;i++)
{
printf("i: %d, n: %d\n", i, envv->n);
		envv->id = i;
		pthread_create(&envv->tid[i], NULL, (void*)f, &envv);
		printf("thread no %d created\n", i);
	}
	for (i=0;i<envv->n;i++)
	{
		pthread_join(envv->tid[i], NULL);
		printf("thread no %d joined\n", i);
	}
}
*/

int main()
{
	t_envv	envv;
	int i =0;
	envv.n = 3;
	init(&envv);

		printf("before : n: %d\n",envv.n);
	envv.n = 3;
	for (i=0;i < envv.n;i++)
	{
		printf("i: %d, n: %d\n", i, envv.n);
		envv.id = i;
		pthread_create(&envv.tid[i], NULL, (void*)f, &envv);
		printf("thread no %d created\n", i);
	}
	for (i=0;i<envv.n;i++)
	{
		pthread_join(envv.tid[i], NULL);
		printf("thread no %d joined\n", i);
	}
}

