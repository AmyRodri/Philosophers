/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:05:03 by amyrodri          #+#    #+#             */
/*   Updated: 2025/11/10 18:54:43 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	should_continue(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->finish_lock);
	if (data->finished)
	{
		pthread_mutex_unlock(&data->finish_lock);
		return (false);
	}
	pthread_mutex_unlock(&data->finish_lock);
	pthread_mutex_lock(&data->meal_lock);
	if (data->num_meals != -1 && philo->meals_eaten >= data->num_meals)
	{
		pthread_mutex_unlock(&data->meal_lock);
		return (false);
	}
	pthread_mutex_unlock(&data->meal_lock);
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (!should_continue(philo, data))
			break ;
		eat(philo);
		print_state(philo, MSG_SLEEP);
		ft_usleep(data->time_to_sleep);
		print_state(philo, MSG_THINKING);
	}
	return (NULL);
}
