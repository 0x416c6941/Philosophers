/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 01:40:19 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 03:00:42 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINES_H
# define ROUTINES_H

# include <structs_and_defines.h>
# include <pthread.h>

/**
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */
/**
 * philos routine.
 * @param	data	Argument of a philo passed by pthread_create().
 * @return	0 is always returned.
 */
void			*ft_philo_routine(struct s_philo *data);

/**
 * Gets the mutex of a first fork for philo.
 * If a philos id is even, we'll first take right fork;
 * if otherwise, we'll take a left fork first.
 * We can do this, since subject doesn't specify in which order we must take
 * forks: "a philosopher takes their right and their left forks to eat, one
 * in each hand". However, there's no order, it's just a set of forks to take.
 * @param	data	Philos data.
 * @return	Mutex of a first fork.
 */
pthread_mutex_t	*ft_get_first_fork(struct s_philo *data);

/**
 * Gets the mutex of a second fork for philo.
 * If a philos id is even, we'll take left fork as a second;
 * if otherwise, we'll take a second fork as a second.
 * We can do this, since subject doesn't specify in which order we must take
 * forks: "a philosopher takes their right and their left forks to eat, one
 * in each hand". However, there's no order, it's just a set of forks to take.
 * @param	data	Philos data.
 * @return	Mutex of a first fork.
 */
pthread_mutex_t	*ft_get_second_fork(struct s_philo *data);

/**
 * Watchdog routine.
 * @param	data	Program's data.
 * @return	0 is always returned.
 */
void			*ft_watchdog_routine(struct s_data *data);

#endif	/* ROUTINES_H */
