/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamys <kamys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:30:18 by kamys             #+#    #+#             */
/*   Updated: 2025/11/02 19:04:31 by kamys            ###   ########.fr       */
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

// validate.c
t_bool	validate(int num, char **args);
t_bool	is_number(char *str);

// utls.c
void	*write_error(char *msg, void *ret);
long	ft_atol(const char *str);

// main.c
// int	main(int num, char **args);

#endif