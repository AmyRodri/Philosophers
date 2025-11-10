/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:19:47 by kamys             #+#    #+#             */
/*   Updated: 2025/11/10 19:14:37 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->finish_lock);
	pthread_mutex_destroy(&data->meal_lock);
	free(data->forks);
	free(data);
}

static t_bool	start_simulation(t_philo *philo, t_data *data)
{
	int			i;

	i = -1;
	while (++i < data->num_philos)
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
			return (false);
	if (data->num_philos > 1)
		if (pthread_create(&data->monitor_thread, NULL, monitor, philo) != 0)
			return (false);
	i = -1;
	while (++i < data->num_philos)
		pthread_join(philo[i].thread, NULL);
	if (data->num_philos > 1)
		pthread_join(data->monitor_thread, NULL);
	return (true);
}

int	main(int num, char **args)
{
	t_philo	*philo;

	if (!validate(num, args))
		return (1);
	philo = setup(num, args);
	if (!philo)
		return (1);
	if (start_simulation(philo, philo[0].data))
	{
		cleanup(philo[0].data);
		free(philo);
		return (1);
	}
	cleanup(philo[0].data);
	free(philo);
	return (0);
}
