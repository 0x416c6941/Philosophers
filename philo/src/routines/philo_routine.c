/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 01:42:21 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 02:50:23 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <routines.h>
#include <structs_and_defines.h>
#include <pthread.h>
#include <stdio.h>
#include <time_stuff.h>

/**
 * If we have only one philo, don't do anything
 * and just wait for watchdog to kill us.
 * @param	data	Program's data.
 * @return	0 is always returned.
 */
static void	*ft_lonely_philo_routine(struct s_data *data)
{
	while (42)
	{
		if (!data->some_philo_died)
			continue ;
		break ;
	}
	return (0);
}

/**
 * Checks if some philo died yet or not.
 * If no philo died yet, mutex will be locked.
 * TODO: is this a correct solution? Or should it be unlocked immediately?
 * @param	data	Program's data.
 * @return	true, if yes;
 * 			false, if no.
 */
static bool	ft_check_death(struct s_data *data)
{
	(void)pthread_mutex_lock(&data->death_lock);
	if (!data->some_philo_died)
		return (false);
	(void)pthread_mutex_unlock(&data->death_lock);
	return (true);
}

void	*ft_philo_routine(struct s_philo *data)
{
	if (data->main_data->args.num_of_philos == 1)
		return (ft_lonely_philo_routine(data->main_data));
	else if (data->main_data->args.cycles == 0)
		return ((void *)0);
	while (42)
	{
		(void)pthread_mutex_lock(ft_get_first_fork(data));
		if (ft_check_death(data->main_data))
			return ((void)pthread_mutex_unlock(ft_get_first_fork(data)), (void *)0);
		(void)pthread_mutex_lock(&data->main_data->output_lock);
		(void)printf("%ld %d has taken a fork\n",
			ft_get_current_ms() - data->main_data->start_time, data->id + 1);
		(void)pthread_mutex_unlock(&data->main_data->output_lock);
		(void)pthread_mutex_unlock(&data->main_data->death_lock);
		(void)pthread_mutex_lock(ft_get_second_fork(data));
		if (ft_check_death(data->main_data))
			return ((void)pthread_mutex_unlock(ft_get_first_fork(data)),
				(void)pthread_mutex_unlock(ft_get_second_fork(data)), (void *)0);
		(void)pthread_mutex_lock(&data->main_data->output_lock);
		(void)printf("%ld %d has taken a fork\n",
			ft_get_current_ms() - data->main_data->start_time, data->id + 1);
		(void)printf("%ld %d is eating\n",
			ft_get_current_ms() - data->main_data->start_time, data->id + 1);
		(void)pthread_mutex_lock(&data->meal_lock);
		data->last_meal = ft_get_current_ms();
		data->meals_eaten++;
		(void)pthread_mutex_unlock(&data->meal_lock);
		(void)pthread_mutex_unlock(&data->main_data->output_lock);
		(void)pthread_mutex_unlock(&data->main_data->death_lock);
		ft_usleep(data->main_data->args.time_to_eat);
		(void)pthread_mutex_unlock(ft_get_first_fork(data));
		(void)pthread_mutex_unlock(ft_get_second_fork(data));
		if ((data->main_data->args.cycles != -1
				&& data->meals_eaten >= data->main_data->args.cycles)
			|| ft_check_death(data->main_data))
			return ((void *)0);
		(void)pthread_mutex_lock(&data->main_data->output_lock);
		(void)printf("%ld %d is sleeping\n",
			ft_get_current_ms() - data->main_data->start_time, data->id + 1);
		(void)pthread_mutex_unlock(&data->main_data->output_lock);
		(void)pthread_mutex_unlock(&data->main_data->death_lock);
		ft_usleep(data->main_data->args.time_to_sleep);
		if (ft_check_death(data->main_data))
			return ((void *)0);
		(void)pthread_mutex_lock(&data->main_data->output_lock);
		(void)printf("%ld %d is thinking\n",
			ft_get_current_ms() - data->main_data->start_time, data->id + 1);
		(void)pthread_mutex_unlock(&data->main_data->output_lock);
		(void)pthread_mutex_unlock(&data->main_data->death_lock);
	}
}
