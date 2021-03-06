/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 23:01:14 by kallard           #+#    #+#             */
/*   Updated: 2020/12/13 14:48:06 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		init_setup_struct(t_setup *setup, int argc, char **argv)
{
	int	i;

	setup->num_of_philos = ft_atoi(argv[1]);
	setup->time_to_die = ft_atoi(argv[2]) * 1000;
	setup->time_to_eat = ft_atoi(argv[3]) * 1000;
	setup->time_to_sleep = ft_atoi(argv[4]) * 1000;
	setup->max_eat_cycles = argc == 6 ? ft_atoi(argv[5]) : 0;
	setup->forks = malloc(sizeof(pthread_mutex_t) * (setup->num_of_philos));
	if (!setup->forks)
		malloc_error();
	setup->one_died = 0;
	setup->count_eating_philos = setup->num_of_philos;
	if (pthread_mutex_init(&setup->writing, NULL))
		init_error();
	if (pthread_mutex_init(&setup->decreasing_count_eating_philos, NULL))
		init_error();
	i = 0;
	while (i < setup->num_of_philos)
		if (pthread_mutex_init(&setup->forks[i++], NULL))
			init_error();
	if (gettimeofday(&setup->start, NULL))
		init_error();
	setup->start.tv_usec = (setup->start.tv_usec / 1000) * 1000;
}

void		init_philo_structs2(t_philo *philos, t_setup *setup)
{
	int	i;
	int j;

	i = 0;
	while (i < setup->num_of_philos)
	{
		j = 0;
		while (j < 10)
			philos[i].actions[j++] = 0;
		philos[i].right_fork = &(setup->forks[i]);
		if (philos[i].index == setup->num_of_philos)
			philos[i].left_fork = &(setup->forks[0]);
		else
			philos[i].left_fork = &(setup->forks[i + 1]);
		i++;
	}
}

void		init_philo_structs(t_philo *philos, t_setup *setup)
{
	int			i;
	uint64_t	start_time;

	start_time = (time_passed(setup->start) / 1000) * 1000 + 0;
	i = 0;
	while (i < setup->num_of_philos)
	{
		philos[i].index = i + 1;
		philos[i].setup = setup;
		philos[i].left_hand = 0;
		philos[i].right_hand = 0;
		philos[i].is_dead = 0;
		philos[i].num_of_dinners = 0;
		philos[i].last_dinner_time = start_time;
		philos[i].next_event_time = 0;
		philos[i].expected_dead_time = philos[i].last_dinner_time + \
										setup->time_to_die + 800;
		if (pthread_mutex_init(&philos[i].eating, NULL))
			init_error();
		i++;
	}
	init_philo_structs2(philos, setup);
}
