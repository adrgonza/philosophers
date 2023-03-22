#include <stdio.h>
#include <pthread.h>

// Chaque thread comptera TIMES_TO_COUNT fois
#define TIMES_TO_COUNT 21000

#define NC	"\e[0m"
#define YELLOW	"\e[33m"
#define BYELLOW	"\e[1;33m"
#define RED	"\e[31m"
#define GREEN	"\e[32m"

// Structure pour contenir le compte ainsi que le mutex qui
// protegera l'accès à cette variable.
typedef	struct s_counter
{
	pthread_mutex_t	count_mutex;
	unsigned int	count;
} t_counter;

void	*thread_routine(void *data)
{
	// Chaque thread commence ici
	pthread_t	tid;
	t_counter	*counter; // pointeur vers la structure dans le main
	unsigned int	i;

	tid = pthread_self();
	counter = (t_counter *)data;
	// On imprime le compte avant que ce thread commence
	// a itérer. Pour lire la valeur de count, on verrouille le
	// mutex.
	pthread_mutex_lock(&counter->count_mutex);
	printf("%sThread [%ld]: compte au depart = %u.%s\n",
		YELLOW, tid, counter->count, NC);
	pthread_mutex_unlock(&counter->count_mutex);
	i = 0;
	while (i < TIMES_TO_COUNT)
	{
		// On itere TIMES_TO_COUNT fois
		// On verouille le mutex le temps
		// d'incrementer le compte
		pthread_mutex_lock(&counter->count_mutex);
		counter->count++;
		pthread_mutex_unlock(&counter->count_mutex);
		i++;
	}
	// On imprime le compte final au moment ou ce thread
	// a termine son propre compte en verouillant le mutex
	pthread_mutex_lock(&counter->count_mutex);
	printf("%sThread [%ld]: Compte final = %u.%s\n",
		BYELLOW, tid, counter->count, NC);
	pthread_mutex_unlock(&counter->count_mutex);
	return (NULL); // Thread termine ici.
}

int	main(void)
{
	pthread_t	tid1;
	pthread_t	tid2;
	// Structure pour contenir le compte des deux threads :
	t_counter	counter;

	// Il n'y a ici qu'un seul thread, on peut donc initialiser
	// le compte sans mutex.
	counter.count = 0;
	// Initialisation du mutex :
	pthread_mutex_init(&counter.count_mutex, NULL);
	// Vu que chaque thread va compter TIMES_TO_COUNT fois et qu'on va
	// avoir 2 threads, on s'attend a ce que le compte final soit
	// 2 * TIMES_TO_COUNT :
	printf("Main: Le compte attendu est de %s%u%s\n", GREEN, 
					2 * TIMES_TO_COUNT, NC);
	// Creation des threads :
	pthread_create(&tid1, NULL, thread_routine, &counter);
	printf("Main: Creation du premier thread [%ld]\n", tid1);
	pthread_create(&tid2, NULL, thread_routine, &counter);
	printf("Main: Creation du second thread [%ld]\n", tid2);
	// Recuperation des threads :
	pthread_join(tid1, NULL);
	printf("Main: Union du premier thread [%ld]\n", tid1);
	pthread_join(tid2, NULL);
	printf("Main: Union du second thread [%ld]\n", tid2);
	// Evaluation du compte final :
	// (Ici on peut lire le compte sans s'occuper du mutex
	// car tous les threads sont unis et on a la garantie
	// qu'un seul un thread va y acceder.)
	if (counter.count != (2 * TIMES_TO_COUNT))
		printf("%sMain: ERREUR ! Le compte est de %u%s\n",
					RED, counter.count, NC);
	else
		printf("%sMain: OK. Le compte est de %u%s\n",
					GREEN, counter.count, NC);
	// On detruit le mutex à la fin du programme :
	pthread_mutex_destroy(&counter.count_mutex);
	return (0);
}
