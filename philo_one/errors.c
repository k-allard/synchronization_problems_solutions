/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kallard <kallard@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 23:39:51 by kallard           #+#    #+#             */
/*   Updated: 2020/12/11 10:25:29 by kallard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	init_error(void)
{
	char	*string;

	string = "ERROR: Cannot initialize simulation\n";
	write(2, string, ft_strlen(string));
	exit(ERROR);
}

void	args_error(void)
{
	char	*string;

	string = "ERROR: Wrong arguments\n";
	write(2, string, ft_strlen(string));
	exit(ERROR);
}

void	malloc_error(void)
{
	char	*string;

	string = "ERROR: Memory allocation error\n";
	write(2, string, ft_strlen(string));
	exit(ERROR);
}
