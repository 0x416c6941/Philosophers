/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:42:04 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/03 01:47:26 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINES_H
# define ROUTINES_H

# include <structs_and_defines.h>
# include <stdbool.h>

/* What to log with ft_log(). */
enum e_log_what
{
	FORK,
	FORK_AND_EATING,
	SLEEPING,
	THINKING,
	DIED
};

/* For ft_philo_think() in philo_routine.c. */
enum e_think_mode
{
	SILENT,
	WITH_LOGGING
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
 * printf()s \p action of a \p philo.
 * @warning	Lock the simulation finish mutex before calling this function!
 * @param	philo	Which philo does some action.
 * @param	action	Which action exactly is it.
 */
void	ft_log(struct s_philo *philo, enum e_log_what action);

#endif	/* ROUTINES_H */
