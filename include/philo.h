/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amyrodri <amyrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:30:18 by kamys             #+#    #+#             */
/*   Updated: 2025/11/03 11:30:51 by amyrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_INT 2147483647

typedef enum s_bool
{
	false = 0,
	true = 1
}	t_bool;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	long			start_time;
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
void	write_error(char *msg);
long	ft_atol(const char *str);

// main.c
// int	main(int num, char **args);

#endif