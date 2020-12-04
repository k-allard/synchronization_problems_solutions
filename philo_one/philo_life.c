#include "philo_one.h"

void	unlock_forks(t_philo *philo)
{
	if (philo->left_hand)
		pthread_mutex_unlock(philo->left_fork);
	if (philo->right_hand)
		pthread_mutex_unlock(philo->right_fork);
	philo->left_hand = 0;
	philo->right_hand = 0;
}

void	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo->actions[TAKEN_LEFT_FORK] = 1;
	philo->left_hand = 1;
	what_status(philo, time_passed(philo->setup->start) / 1000);
	pthread_mutex_lock(philo->right_fork);
	philo->actions[TAKEN_RIGHT_FORK] = 1;
	philo->right_hand = 1;
	what_status(philo, time_passed(philo->setup->start) / 1000);
}

void	eating(t_philo *philo)
{
	philo->is_eating = 1;
	philo->last_dinner_time = time_passed(philo->setup->start);
	philo->actions[EATING] = 1;
	what_status(philo, time_passed(philo->setup->start) / 1000);
	wait_me(philo->setup->start, philo->last_dinner_time, philo->setup->time_to_eat);
	philo->num_of_dinners++;
	philo->is_eating = 0;
}

int		max_cycles_reached(t_philo *philo)
{
	if (philo->setup->max_eat_cycles && philo->num_of_dinners >= philo->setup->max_eat_cycles)
	{
		pthread_mutex_unlock(&(philo->has_eaten_enough_times));
		return (1);
	}
	return (0);
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
		philo->actions[THINKING] = 1;
		what_status(philo, time_passed(philo->setup->start) / 1000);
		lock_forks(philo);
		eating(philo);
		unlock_forks(philo);
		if (max_cycles_reached(philo))
			return (NULL);
		philo->actions[SLEEPING] = 1;
		what_status(philo, time_passed(philo->setup->start) / 1000);
		wait_me_2(philo->setup->time_to_sleep);
	}
	unlock_forks(philo);
	pthread_mutex_unlock(&(philo->has_eaten_enough_times));

	return (NULL);
}
