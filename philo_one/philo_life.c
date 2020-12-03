#include "philo_one.h"

void	eating(t_philo *philo)
{
	philo->is_eating = 1;
	philo->last_dinner_time = time_passed(philo->setup->start);
	philo->alerts[EATING] = 1;
	what_status(philo, time_passed(philo->setup->start) / 1000);
	wait_me(philo->setup->start, philo->last_dinner_ts, philo->setup->time_to_eat);
	philo->num_of_dinners++;
	philo->is_eating = 0;
}

void	*philo_entry_function(void *argument) // When creating a thread, we need to point it to a function for it to start execution.
// The function must return void * and take a single void * argument.
{
	t_philo *philo;
	pthread_t supervisor;

	philo = argument;
	pthread_create(&supervisor, NULL, &supervisor_function, argument);
	pthread_detach(supervisor);
	while (42 && !philo->setup->can_stop)
	{
		philo->alerts[THINKING] = 1;
	}



	return (NULL);
}
