/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 18:46:47 by kamys             #+#    #+#             */
/*   Updated: 2025/11/10 18:42:35 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_error(char *msg)
{
	write(2, "\033[31mError: \033[0m", 17);
	while (*msg)
		write(2, msg++, 1);
}

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0));
}

void	ft_usleep(long duration)
{
	long	start_time;

	start_time = (long)get_time();
	while ((long)(get_time() - start_time) < duration)
		usleep(100);
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

void	*print_state(t_philo *philo, const char *state)
{
	pthread_mutex_lock(&philo->data->finish_lock);
	if (!philo->data->finished)
		printf("\033[1;97m%-5ld \033[2;37m%-2d\033[0;97m %s\033[0m\n",
			get_time() - philo->data->start_time,
			philo->id, state);
	pthread_mutex_unlock(&philo->data->finish_lock);
	return (NULL);
}
