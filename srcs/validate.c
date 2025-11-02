/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:45:27 by kamys             #+#    #+#             */
/*   Updated: 2025/11/02 19:03:49 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_number(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

t_bool	validate(int num, char **args)
{
	long	i;

	if (num < 5 || num > 6)
		return (false);
	while (--num)
	{
		if (!is_number(args[num]))
			return ((t_bool)write_error("Argument is not a number\n", false));
		i = ft_atol(args[num]);
		if (i < 0 || i > MAX_INT)
			return ((t_bool)write_error("Argument out of range\n", false));
	}
	return (true);
}
