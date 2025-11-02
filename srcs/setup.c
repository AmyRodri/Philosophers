/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 20:33:15 by kamys             #+#    #+#             */
/*   Updated: 2025/11/02 20:34:00 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_data	*init_data(int num, char **args)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (write_error("Memory allocation failed\n", NULL));
	data->num_philos = (int)ft_atol(args[1]);
	data->time_to_die = (int)ft_atol(args[2]);
	data->time_to_eat = (int)ft_atol(args[3]);
	data->time_to_sleep = (int)ft_atol(args[4]);
	data->num_meals = 0;
	if (num == 6)
		data->num_meals = (int)ft_atol(args[5]);
	return (data);
}

static t_philo	*init_philo(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!philos)
		return (write_error("Memory allocation failed\n", NULL));
	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		i++;
	}
	return (philos);
}

t_philo	*setup(int num, char **args)
{
	t_philo	*philos;
	t_data	*data;
	int		i;

	data = init_data(num, args);
	if (!data)
		return (NULL);
	philos = init_philo(data);
	if (!philos)
	{
		free(data);
		return (NULL);
	}
	return (philos);
}
