/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:30:18 by kamys             #+#    #+#             */
/*   Updated: 2025/11/02 20:34:33 by kamys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define MAX_INT 2147483647

typedef enum s_bool
{
	false = 0,
	true = 1
}	t_bool;

typedef struct s_data
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_meals;
}	t_data;

typedef struct s_philo
{
	int		id;
	t_data	*data;
}	t_philo;

// validate.c
t_bool	validate(int num, char **args);
t_bool	is_number(char *str);

// setup.c
t_philo	*setup(int num, char **args);

// utls.c
void	*write_error(char *msg, void *ret);
long	ft_atol(const char *str);

// main.c
// int	main(int num, char **args);

#endif