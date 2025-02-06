/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:33:53 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/03 02:38:43 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <routines.h>
#include <structs_and_defines.h>
#include <stdbool.h>
#include <time_stuff.h>
#include <pthread.h>
#include <unistd.h>

/**
 * Try to kill the \p philo.
 * If \p philo hasn't eaten required amount of times,
 * \p everybody_ate_enough will be set to false.
 * If \p philo is killed, it will be logged.
 * @param	philo					Philo to try to kill.
 * @param	everybody_ate_enough	External parameter that keeps track if all
 * 									philos ate a required amount of times.
 * @return	true, if philo was killed successfully;
 * 			false otherwise.
 */
static bool	ft_kill_philo(struct s_philo *philo, bool *everybody_ate_enough)
{
	(void)pthread_mutex_lock(&philo->meal_lock);
	if ((ft_get_current_ms() - philo->last_meal)
		>= philo->main_data->args.time_to_die)
		return ((void)pthread_mutex_lock(&philo->main_data->finish_lock),
			ft_log(philo, DIED),
			philo->main_data->finished = true,
			(void)pthread_mutex_unlock(&philo->main_data->finish_lock),
			(void)pthread_mutex_unlock(&philo->meal_lock), true);
	if (philo->meals_eaten < philo->main_data->args.cycles)
		*everybody_ate_enough = false;
	(void)pthread_mutex_unlock(&philo->meal_lock);
	return (false);
}

#define SUSPEND_WATCHDOG	1000

void	*ft_watchdog_routine(struct s_data *data)
{
	bool	everybody_ate_enough;
	int		i;

	ft_wait_until(data->start_time);
	while (42)
	{
		everybody_ate_enough = true;
		if (data->args.cycles == -1)
			everybody_ate_enough = false;
		i = 0;
		while (i < data->args.num_of_philos)
		{
			if (ft_kill_philo(&data->philos[i], &everybody_ate_enough))
				return ((void *)0);
			i++;
		}
		if (everybody_ate_enough)
			return ((void)pthread_mutex_lock(&data->finish_lock),
				data->finished = true,
				(void)pthread_mutex_unlock(&data->finish_lock), (void *)0);
		usleep(SUSPEND_WATCHDOG);
	}
}
