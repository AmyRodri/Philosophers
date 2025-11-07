/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:05:03 by amyrodri          #+#    #+#             */
/*   Updated: 2025/11/07 19:09:39 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*print_state(t_philo *philo, const char *state)
{
	pthread_mutex_lock(&philo->data->write_lock);
	if (!philo->data->finished)
		printf("%-5ld %-2d %s\n", get_time() - philo->data->start_time,
			philo->id, state);
	pthread_mutex_unlock(&philo->data->write_lock);
	return (NULL);
}

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_state(philo, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_state(philo, "has taken a fork");
	}
	pthread_mutex_lock(&data->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->meal_lock);
	print_state(philo, "is eating");
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
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
		pthread_mutex_lock(&data->finish_lock);
		if (data->finished)
		{
			pthread_mutex_unlock(&data->finish_lock);
			break ;
		}
		pthread_mutex_unlock(&data->finish_lock);
		eat(philo);
		print_state(philo, "is sleeping");
		ft_usleep(data->time_to_sleep);
		pthread_mutex_lock(&data->meal_lock);
		if (data->num_meals != -1 && philo->meals_eaten >= data->num_meals)
			break ;
		pthread_mutex_unlock(&data->meal_lock);
		print_state(philo, "is thinking");
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	size_t	time_since_meal;
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
			pthread_mutex_lock(&data->meal_lock);
			time_since_meal = get_time() - philo[i].last_meal;
			pthread_mutex_unlock(&data->meal_lock);
			if (time_since_meal > data->time_to_die)
			{
				// pthread_mutex_lock(&data->write_lock);
				// printf("%-5ld %-2d died\n", get_time() - data->start_time,
				// 	philo[i].id + 1);
				// pthread_mutex_unlock(&data->write_lock);
				// pthread_mutex_lock(&data->finish_lock);
				print_state(philo, "died");
				data->finished = 1;
				pthread_mutex_unlock(&data->finish_lock);
				return (NULL);
			}
			pthread_mutex_lock(&data->meal_lock);
			if (data->num_meals != -1
				&& philo[i].meals_eaten >= data->num_meals)
				done++;
			pthread_mutex_unlock(&data->meal_lock);
			i++;
		}
		if (data->num_meals != -1 && done == data->num_philos)
		{
			pthread_mutex_lock(&data->finish_lock);
			data->finished = 1;
			pthread_mutex_unlock(&data->finish_lock);
			return (NULL);
		}
	}
	return (NULL);
}
