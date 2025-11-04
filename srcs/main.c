/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:19:47 by kamys             #+#    #+#             */
/*   Updated: 2025/11/04 11:48:29 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	sla(t_philo *philo, t_data *data)
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

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->finish_lock);
	free(data->forks);
	free(data);
}

int	main(int num, char **args)
{
	t_philo	*philo;

	if (!validate(num, args))
		return (1);
	philo = setup(num, args);
	if (!philo)
		return (1);
	if (sla(philo, philo[0].data))
	{
		cleanup(philo[0].data);
		return (1);
	}
	cleanup(philo[0].data);
	free(philo);
	return (0);
}
