/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:02:43 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/03 02:39:39 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <routines.h>
#include <structs_and_defines.h>
#include <pthread.h>
#include <time_stuff.h>
#include <unistd.h>
#include <stdbool.h>

/**
 * Philos eating routine.
 * @param	arg	Philos data.
 * @return	true, if simulation hasn't stopped;
 * 			false, if simulation has stopped
 * 				(or if philo ate required amount of times).
 */
static bool	ft_philo_eat(struct s_philo *arg)
{
	(void)pthread_mutex_lock(arg->f_fork);
	(void)pthread_mutex_lock(&arg->main_data->finish_lock);
	if (arg->main_data->finished)
		return ((void)pthread_mutex_unlock(&arg->main_data->finish_lock),
			(void)pthread_mutex_unlock(arg->f_fork), false);
	ft_log(arg, FORK);
	(void)pthread_mutex_unlock(&arg->main_data->finish_lock);
	(void)pthread_mutex_lock(arg->s_fork);
	(void)pthread_mutex_lock(&arg->main_data->finish_lock);
	if (arg->main_data->finished)
		return ((void)pthread_mutex_unlock(&arg->main_data->finish_lock),
			(void)pthread_mutex_unlock(arg->s_fork),
			(void)pthread_mutex_unlock(arg->f_fork), false);
	ft_log(arg, FORK_AND_EATING);
	(void)pthread_mutex_unlock(&arg->main_data->finish_lock);
	ft_usleep(arg->main_data->args.time_to_eat);
	(void)pthread_mutex_lock(&arg->meal_lock);
	arg->last_meal = ft_get_current_ms();
	arg->meals_eaten++;
	(void)pthread_mutex_unlock(arg->s_fork);
	(void)pthread_mutex_unlock(arg->f_fork);
	if (arg->main_data->args.cycles != -1
		&& arg->meals_eaten >= arg->main_data->args.cycles)
		return ((void)pthread_mutex_unlock(&arg->meal_lock), false);
	return ((void)pthread_mutex_unlock(&arg->meal_lock), true);
}

/**
 * Philos sleeping routine.
 * @param	arg	Philos data.
 * @return	true, if simulation hasn't stopped;
 * 			false, if simulation has stopped.
 */
static bool	ft_philo_sleep(struct s_philo *arg)
{
	(void)pthread_mutex_lock(&arg->main_data->finish_lock);
	if (arg->main_data->finished)
		return ((void)pthread_mutex_unlock(&arg->main_data->finish_lock),
			false);
	ft_log(arg, SLEEPING);
	(void)pthread_mutex_unlock(&arg->main_data->finish_lock);
	ft_usleep(arg->main_data->args.time_to_sleep);
	return (true);
}

/* Thanks a lot to @mcombeau! */
#define TOO_MUCH_THINKING_TIME		600
#define THINKING_TIME_UPPER_FLOOR	200

/**
 * Philos thinking routine.
 * To make sure that some philo doesn't get too greedy,
 * it would get suspended a bit, however not too much,
 * so that it doesn't starve to death.
 * @param	arg			Philos data.
 * @param	think_mode	Whether thinking should be logged or not.
 * @return	true, if simulation hasn't stopped;
 * 			false, if simulation has stopped.
 */
static bool	ft_philo_think(struct s_philo *arg, enum e_think_mode think_mode)
{
	long	time_to_think;

	(void)pthread_mutex_lock(&arg->meal_lock);
	time_to_think = (arg->main_data->args.time_to_die
			- (ft_get_current_ms() - arg->last_meal)
			- arg->main_data->args.time_to_eat) / 2;
	(void)pthread_mutex_unlock(&arg->meal_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && think_mode == SILENT)
		time_to_think = 1;
	if (time_to_think > TOO_MUCH_THINKING_TIME)
		time_to_think = THINKING_TIME_UPPER_FLOOR;
	(void)pthread_mutex_lock(&arg->main_data->finish_lock);
	if (arg->main_data->finished)
		return ((void)pthread_mutex_unlock(&arg->main_data->finish_lock),
			false);
	if (think_mode == WITH_LOGGING)
		ft_log(arg, THINKING);
	(void)pthread_mutex_unlock(&arg->main_data->finish_lock);
	ft_usleep(time_to_think);
	return (true);
}

#undef THINKING_TIME_UPPER_FLOOR
#undef TOO_MUCH_THINKING_TIME

/* There's no need to check the finish flag in the beginning,
 * as we know that simulation can't finish when it hasn't even started yet. */
void	*ft_philo_routine(struct s_philo *arg)
{
	(void)pthread_mutex_lock(&arg->meal_lock);
	arg->last_meal = arg->main_data->start_time;
	arg->meals_eaten = 0;
	(void)pthread_mutex_unlock(&arg->meal_lock);
	if (arg->main_data->args.num_of_philos == 0
		|| arg->main_data->args.time_to_die == 0
		|| arg->main_data->args.cycles == 0)
		return ((void *)0);
	ft_wait_until(arg->main_data->start_time);
	if ((arg->id % 2) == 0)
		ft_philo_think(arg, SILENT);
	while (42)
	{
		if (ft_philo_eat(arg) == false || ft_philo_sleep(arg) == false
			|| ft_philo_think(arg, WITH_LOGGING) == false)
			return ((void *)0);
	}
}
