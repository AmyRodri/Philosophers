/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 20:33:15 by kamys             #+#    #+#             */
/*   Updated: 2025/11/07 19:01:22 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_data	*init_data(int num, char **args)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		write_error("Memory allocation failed\n");
		return (NULL);
	}
	data->num_philos = (int)ft_atol(args[1]);
	data->time_to_die = (int)ft_atol(args[2]);
	data->time_to_eat = (int)ft_atol(args[3]);
	data->time_to_sleep = (int)ft_atol(args[4]);
	data->num_meals = -1;
	data->finished = 0;
	data->start_time = get_time();
	if (num == 6)
		data->num_meals = (int)ft_atol(args[5]);
	return (data);
}

static t_bool	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		write_error("Memory allocation failed\n");
		return (false);
	}
	i = 0;
	while (i < data->num_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->finish_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	return (true);
}

static t_philo	*init_philo(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!philos)
	{
		write_error("Memory allocation failed\n");
		return (NULL);
	}
	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % data->num_philos;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = data->start_time;
		i++;
	}
	return (philos);
}

t_philo	*setup(int num, char **args)
{
	t_philo	*philos;
	t_data	*data;

	data = init_data(num, args);
	if (!data)
		return (NULL);
	if (!init_mutexes(data))
		return (NULL);
	philos = init_philo(data);
	if (!philos)
	{
		free(data);
		return (NULL);
	}
	return (philos);
}
