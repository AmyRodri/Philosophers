/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:19:47 by kamys             #+#    #+#             */
/*   Updated: 2025/11/02 18:50:08 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int num, char **args)
{
	if (!validate(num, args))
		return (1);
	ft_printf("All arguments are valid!\n");
	return (0);
}
