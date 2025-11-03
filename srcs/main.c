/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:19:47 by kamys             #+#    #+#             */
/*   Updated: 2025/11/03 11:17:45 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int num, char **args)
{
	t_philo	*philos;

	if (!validate(num, args))
		return (1);
	philos = setup(num, args);
	if (!philos)
		return (1);
	free(philos[0].data);
	free(philos);
	printf("finish\n");
	return (0);
}
