/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:05:03 by amyrodri          #+#    #+#             */
/*   Updated: 2025/11/07 23:28:44 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_state(philo, MSG_FORK);
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_state(philo, MSG_FORK);
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_state(philo, MSG_FORK);
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_state(philo, MSG_FORK);
	}
	pthread_mutex_lock(&data->meal_lock);
	philo->last_meal = get_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&data->meal_lock);
	print_state(philo, MSG_EATING);
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
		print_state(philo, MSG_SLEEP);
		ft_usleep(data->time_to_sleep);
		pthread_mutex_lock(&data->meal_lock);
		if (data->num_meals != -1 && philo->meals_eaten >= data->num_meals)
		{
			pthread_mutex_unlock(&data->meal_lock);
			break ;
		}
		pthread_mutex_unlock(&data->meal_lock);
		print_state(philo, MSG_THINKING);
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
				print_state(&philo[i], MSG_DIED);
				pthread_mutex_lock(&data->finish_lock);
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
