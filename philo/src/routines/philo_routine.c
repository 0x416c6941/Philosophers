/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 15:02:43 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 15:53:04 by asagymba         ###   ########.fr       */
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
 * 			false, if simulation has stopped.
 */
static bool	ft_philo_eat(struct s_philo *arg)
{
	(void)pthread_mutex_lock(arg->r_fork);
	(void)pthread_mutex_lock(&arg->main_data->finish_lock);
	if (arg->main_data->finished)
		return ((void)pthread_mutex_unlock(&arg->main_data->finish_lock),
			(void)pthread_mutex_unlock(arg->r_fork), false);
	ft_mutex_printf(arg, FORK);
	(void)pthread_mutex_unlock(&arg->main_data->finish_lock);
	(void)pthread_mutex_lock(arg->l_fork);
	(void)pthread_mutex_lock(&arg->main_data->finish_lock);
	if (arg->main_data->finished)
		return ((void)pthread_mutex_unlock(&arg->main_data->finish_lock),
			(void)pthread_mutex_unlock(arg->l_fork),
			(void)pthread_mutex_unlock(arg->r_fork), false);
	ft_mutex_printf(arg, FORK_AND_EATING);
	(void)pthread_mutex_unlock(&arg->main_data->finish_lock);
	ft_usleep(arg->main_data->args.time_to_eat);
	(void)pthread_mutex_lock(&arg->meal_lock);
	arg->last_meal = ft_get_current_ms();
	arg->meals_eaten++;
	(void)pthread_mutex_unlock(&arg->meal_lock);
	return ((void)pthread_mutex_unlock(arg->l_fork),
		(void)pthread_mutex_unlock(arg->r_fork), true);
}

/**
 * Philos eating routine.
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
	ft_mutex_printf(arg, SLEEPING);
	(void)pthread_mutex_unlock(&arg->main_data->finish_lock);
	ft_usleep(arg->main_data->args.time_to_sleep);
	return (true);
}

/**
 * Philos thinking routine.
 * @param	arg	Philos data.
 * @return	true, if simulation hasn't stopped;
 * 			false, if simulation has stopped.
 */
static bool	ft_philo_think(struct s_philo *arg, bool silent)
{
	long	time_to_think;

	(void)pthread_mutex_lock(&arg->meal_lock);
	time_to_think = (arg->main_data->args.time_to_die
			- (ft_get_current_ms() - arg->last_meal)
			- arg->main_data->args.time_to_eat) / 2;
	(void)pthread_mutex_unlock(&arg->meal_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	(void)pthread_mutex_lock(&arg->main_data->finish_lock);
	if (arg->main_data->finished)
		return ((void)pthread_mutex_unlock(&arg->main_data->finish_lock),
			false);
	if (!silent)
		ft_mutex_printf(arg, THINKING);
	(void)pthread_mutex_unlock(&arg->main_data->finish_lock);
	return (true);
}

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
	if (arg->id % 2 == 0)
		ft_philo_think(arg, true);
	while (42)
	{
		if (ft_philo_eat(arg) == false)
			return ((void *)0);
		(void)pthread_mutex_lock(&arg->meal_lock);
		if (arg->main_data->args.cycles != -1
			&& arg->meals_eaten >= arg->main_data->args.cycles)
			return ((void)pthread_mutex_unlock(&arg->meal_lock), (void *)0);
		(void)pthread_mutex_unlock(&arg->meal_lock);
		if (ft_philo_sleep(arg) == false
			|| ft_philo_think(arg, false) == false)
			return ((void *)0);
	}
}
