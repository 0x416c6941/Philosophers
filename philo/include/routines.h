/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:42:04 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 15:33:40 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINES_H
# define ROUTINES_H

# include <structs_and_defines.h>
# include <stdbool.h>

enum e_mutex_printf
{
	FORK,
	FORK_AND_EATING,
	SLEEPING,
	THINKING,
	DIED
};

/**
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */
/**
 * Philo routine.
 * @param	arg	Argument to pass with pthread_create().
 * @return	0 cast to void * is always returned.
 */
void	*ft_philo_routine(struct s_philo *arg);

/**
 * Watchdog routine.
 * @param	data	Program's data.
 * @return	0 cast to void * is always returned.
 */
void	*ft_watchdog_routine(struct s_data *data);

/**
 * printf()s \p action of a \p philo,
 * while locking and later unlocking printf()s mutex lock.
 * @param	philo	Which philo does some action.
 * @param	action	Which action exactly is it.
 */
void	ft_mutex_printf(struct s_philo *philo, enum e_mutex_printf action);

#endif	/* ROUTINES_H */
