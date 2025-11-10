/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:53:19 by kamys             #+#    #+#             */
/*   Updated: 2025/11/10 18:44:40 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	check_death(t_philo *philo, t_data *data, int i)
{
	size_t	time_since_meal;

	pthread_mutex_lock(&data->meal_lock);
	time_since_meal = get_time() - philo[i].last_meal;
	pthread_mutex_unlock(&data->meal_lock);
	if (time_since_meal > data->time_to_die)
	{
		print_state(&philo[i], MSG_DIED);
		pthread_mutex_lock(&data->finish_lock);
		data->finished = 1;
		pthread_mutex_unlock(&data->finish_lock);
		return (false);
	}
	return (true);
}

static void	update_done_count(t_philo *philo, t_data *data, int *done, int i)
{
	pthread_mutex_lock(&data->meal_lock);
	if (data->num_meals != -1
		&& philo[i].meals_eaten >= data->num_meals)
		(*done)++;
	pthread_mutex_unlock(&data->meal_lock);
}

static t_bool	check_all_meals_done(t_data *data, int done)
{
	if (data->num_meals != -1 && done == data->num_philos)
	{
		pthread_mutex_lock(&data->finish_lock);
		data->finished = 1;
		pthread_mutex_unlock(&data->finish_lock);
		return (false);
	}
	return (true);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		i;
	int		done;

	philo = (t_philo *)arg;
	data = philo[0].data;
	while (1)
	{
		i = 0;
		done = 0;
		while (i < data->num_philos)
		{
			if (!check_death(philo, data, i))
				return (NULL);
			update_done_count(philo, data, &done, i++);
		}
		if (!check_all_meals_done(data, done))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
