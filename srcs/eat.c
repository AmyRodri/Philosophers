/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:54:26 by kamys             #+#    #+#             */
/*   Updated: 2025/11/10 18:59:57 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_forks(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_state(philo, MSG_FORK);
		pthread_mutex_lock(&data->forks[philo->right_fork]);
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_state(philo, MSG_FORK);
		pthread_mutex_lock(&data->forks[philo->left_fork]);
	}
	print_state(philo, MSG_FORK);
}

static void	one_philo(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	print_state(philo, MSG_FORK);
	ft_usleep(data->time_to_die);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	print_state(philo, MSG_DIED);
	pthread_mutex_lock(&data->finish_lock);
	data->finished = 1;
	pthread_mutex_unlock(&data->finish_lock);
}

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->num_philos == 1)
		return (one_philo(philo, data));
	lock_forks(philo, data);
	pthread_mutex_lock(&data->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->meal_lock);
	print_state(philo, MSG_EATING);
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
}
