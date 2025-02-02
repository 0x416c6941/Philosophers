/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watchdog_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 02:51:55 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 03:01:35 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <routines.h>
#include <structs_and_defines.h>
#include <stdbool.h>
#include <pthread.h>
#include <time_stuff.h>
#include <stdio.h>

void	*ft_watchdog_routine(struct s_data *data)
{
	bool	everyone_ate_enough;
	int		i;

	while (42)
	{
		everyone_ate_enough = true;
		i = 0;
		while (i < data->args.num_of_philos)
		{
			(void)pthread_mutex_lock(&data->philos[i].meal_lock);
			if ((ft_get_current_ms()
					- data->philos[i].last_meal) >= data->args.time_to_die)
			{
				(void)pthread_mutex_lock(&data->death_lock);
				data->some_philo_died = true;
				(void)pthread_mutex_unlock(&data->death_lock);
				(void)pthread_mutex_lock(&data->output_lock);
				(void)printf("%ld %d died\n",
					ft_get_current_ms() - data->start_time, i + 1);
				(void)pthread_mutex_unlock(&data->output_lock);
				return ((void)pthread_mutex_unlock(&data->philos[i].meal_lock),
					(void *)0);
			}
			else if (data->args.cycles == -1
				|| data->philos[i].meals_eaten < data->args.cycles)
				everyone_ate_enough = false;
			(void)pthread_mutex_unlock(&data->philos[i++].meal_lock);
		}
		if (everyone_ate_enough)
			return ((void *)0);
	}
}
