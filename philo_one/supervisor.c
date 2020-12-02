#include "philo_one.h"

void	set_action(t_philo *philo, int action)
{
	philo->actions[action] = 1;
}

void	write_status(int time, int philo_id, char *action, pthread_mutex_t *writing)
{
	pthread_mutex_lock(writing);
	ft_putnbr(time);
	write(1, "\t", 1);
	ft_putnbr(philo_id);
	write(1, action, ft_strlen(action));
	pthread_mutex_unlock(writing);
}

void	what_status(t_philo *philo, int time)
{
	if (philo->setup->can_stop)
		return ;
	if (philo->alerts[THINKING])
	{
		write_status(time, philo->index, " is thinking\n", &philo->setup->writing);
		philo->alerts[THINKING] = 0;
	}
	if (philo->alerts[TAKEN_LEFT_FORK])
	{
		write_status(time, philo->index, " has taken a fork\n", &philo->setup->writing);
		philo->alerts[TAKEN_LEFT_FORK] = 0;
	}
	if (philo->alerts[TAKEN_RIGHT_FORK])
	{
		write_status(time, philo->index, " has taken a fork\n", &philo->setup->writing);
		philo->alerts[TAKEN_RIGHT_FORK] = 0;
	}
	if (philo->alerts[EATING])
	{
		write_status(time, philo->index, " is eating\n", &philo->setup->writing);
		philo->alerts[EATING] = 0;
	}
	if (philo->alerts[SLEEPING])
	{
		write_status(time, philo->index, " is sleeping\n", &philo->setup->writing);
		philo->alerts[SLEEPING] = 0;
	}
	if (philo->alerts[DIED])
	{
		write_status(time, philo->index, " is dead\n", &philo->setup->writing);
		philo->alerts[DIED] = 0;
		philo->setup->can_stop = 1;
	}
}

void	*supervisor_function(void *argument)
{
	t_philo *philo;
	uint64_t	time; // в микросекундах

	philo = argument;
	while (!philo->setup->can_stop)
	{
		time = time_passed(philo->setup->start); 	//сколько прошло МИКРОсекунд со старта программы

	}
	return (NULL);
}
