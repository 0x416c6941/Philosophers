/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:33:53 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/03 02:10:49 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <routines.h>
#include <structs_and_defines.h>
#include <stdbool.h>
#include <time_stuff.h>
#include <pthread.h>
#include <unistd.h>

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
			(void)pthread_mutex_lock(&data->philos[i].meal_lock);
			if ((ft_get_current_ms() - data->philos[i].last_meal)
				>= data->args.time_to_die)
				return ((void)pthread_mutex_lock(&data->finish_lock),
					data->finished = true,
					ft_log(&data->philos[i], DIED),
					(void)pthread_mutex_unlock(&data->finish_lock),
					(void)pthread_mutex_unlock(&data->philos[i].meal_lock),
					(void *)0);
			if (data->philos[i].meals_eaten < data->args.cycles)
				everybody_ate_enough = false;
			(void)pthread_mutex_unlock(&data->philos[i].meal_lock);
			i++;
		}
		if (everybody_ate_enough)
			return ((void)pthread_mutex_lock(&data->finish_lock),
				data->finished = true,
				(void)pthread_mutex_unlock(&data->finish_lock), (void *)0);
		usleep(SUSPEND_WATCHDOG);
	}
}
