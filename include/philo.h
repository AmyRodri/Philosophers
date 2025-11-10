/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:30:18 by kamys             #+#    #+#             */
/*   Updated: 2025/11/10 19:13:20 by kamys            ###   ########.fr       */
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

# define MSG_EATING "\033[93mis eating\033[0m"
# define MSG_FORK "\033[95mhas taken a fork\033[0m"
# define MSG_SLEEP "\033[96mis sleeping\033[0m"
# define MSG_THINKING "\033[92mis thinking\033[0m"
# define MSG_DIED "\033[1;91mdied\033[0m"

typedef enum s_bool
{
	false = 0,
	true = 1
}	t_bool;

typedef struct s_data
{
	int				num_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_meals;
	int				finished;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	finish_lock;
	pthread_mutex_t	meal_lock;
	pthread_t		monitor_thread;
	size_t			start_time;
}	t_data;

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	int			left_fork;
	int			right_fork;
	int			meals_eaten;
	size_t		last_meal;
	t_data		*data;
}	t_philo;

// validate.c
t_bool	validate(int num, char **args);

// setup.c
t_philo	*setup(int num, char **args);

// runtime.c
void	*routine(void *arg);

// monitor.c
void	*monitor(void *arg);

// eat.c
void	eat(t_philo *philo);

// utls.c
void	write_error(char *msg);
long	get_time(void);
void	ft_usleep(long duration);
long	ft_atol(const char *str);
void	*print_state(t_philo *philo, const char *state);

// main.c
// int	main(int num, char **args);

#endif