/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:45:27 by kamys             #+#    #+#             */
/*   Updated: 2025/11/10 18:40:17 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	is_number(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

static t_bool	number_arguments(int num)
{
	if (num < 5 || num > 6)
	{
		write_error(
			"usage ->\033[34m ./philo "
			"number_of_philosophers "
			"time_to_die time_to_eat "
			"time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\033[0m\n"
			);
		return (false);
	}
	return (true);
}

t_bool	validate(int num, char **args)
{
	long	i;

	if (!number_arguments(num))
		return (false);
	while (--num)
	{
		if (!is_number(args[num]))
		{
			write_error("Argument is not a number\n");
			return (false);
		}
		i = ft_atol(args[num]);
		if (i < 0 || i > MAX_INT)
		{
			write_error("Argument out of range\n");
			return (false);
		}
	}
	return (true);
}
