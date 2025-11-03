/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:19:47 by kamys             #+#    #+#             */
/*   Updated: 2025/11/03 17:02:41 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sla(t_philo *philo, t_data *data)
{
	pthread_t	monitor_thread;
	int			i;

	i = -1;
	while (++i < data->num_philos)
		pthread_create(&philo[i].thread, NULL, routine, &philo[i]);
	pthread_create(&monitor_thread, NULL, monitor, philo);
	i = -1;
	while (++i < data->num_philos)
		pthread_join(philo[i].thread, NULL);
	pthread_join(monitor_thread, NULL);

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
	sla(philo, philo[0].data);
	cleanup(philo[0].data);
	free(philo);
	return (0);
}
