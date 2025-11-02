/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:46:47 by kamys             #+#    #+#             */
/*   Updated: 2025/11/02 19:00:41 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	putstr_fd(const char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}

void	*write_error(char *msg, void *ret)
{
	putstr_fd("Error: ", 2);
	putstr_fd(msg, 2);
	return (ret);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	result = 0;
	while (*str >= '0' && *str <= '9')
		result = result * 10 + (*str++ - '0');
	return (result * sign);
}
