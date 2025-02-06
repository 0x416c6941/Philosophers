/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:38:21 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/04 14:24:52 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <init.h>
#include <structs_and_defines.h>
#include <utils.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <pthread.h>

int	ft_init_args(int argc, char *argv[], struct s_args *out)
{
	int	*current_out_field;
	int	read_arg;

	current_out_field = (int *)out;
	while (argc != 0)
	{
		while (ft_isspace(**argv))
			(*argv)++;
		if (**argv == '\0')
			return (ft_errmsg(EMPTY_ARG_MSG, WITH_NEWLINE), -1);
		else if (ft_atoi_modified((const char **)argv, &read_arg) == -1)
			return (ft_errmsg(INVALID_ARG_MSG, WITH_NEWLINE), -1);
		if (!(read_arg >= 0))
			return (ft_errmsg(ARG_IS_NEGATIVE_MSG, WITH_NEWLINE), -1);
		while (ft_isspace(**argv))
			(*argv)++;
		if (**argv != '\0')
			return (ft_errmsg(INVALID_ARG_MSG, WITH_NEWLINE), -1);
		*current_out_field++ = read_arg;
		argc--;
		argv++;
	}
	return (0);
}

/**
 * Norminette Bypass.
 * Allocate memory for forks in \p out and initialize their mutexes.
 * @param	out	Where to save the forks.
 * @return	-1, if something went wrong;
 * 			Some non-negative value, if everything went ok.
 */
static int	ft_init_forks(struct s_data *out)
{
	int	i;
	int	j;

	out->forks = (pthread_mutex_t *)malloc((long unsigned int)out
			->args.num_of_philos * sizeof(pthread_mutex_t));
	if (out->forks == NULL)
		return (-1);
	i = 0;
	while (i < out->args.num_of_philos)
	{
		if (pthread_mutex_init(&out->forks[i], NULL) == -1)
		{
			j = 0;
			while (j < i)
				(void)pthread_mutex_destroy(&out->forks[j++]);
			free(out->forks);
			out->forks = NULL;
			return (-1);
		}
		i++;
	}
	return (0);
}

/**
 * Yet another Norminette Bypass.
 * Sets forks in \p philo depending on \p i.
 * @param	philo	Philo.
 * @param	i		Id of \p philo.
 */
static void	ft_philo_set_forks(struct s_philo *philo)
{
	const int	idx = philo->id - 1;

	if ((philo->id % 2) == 0)
	{
		philo->f_fork = &philo->main_data->forks[idx];
		if (idx == 0)
			philo->s_fork = &philo->main_data->forks
			[philo->main_data->args.num_of_philos - 1];
		else
			philo->s_fork = &philo->main_data->forks[idx - 1];
	}
	else
	{
		if (idx == 0)
			philo->f_fork = &philo->main_data->forks
			[philo->main_data->args.num_of_philos - 1];
		else
			philo->f_fork = &philo->main_data->forks[idx - 1];
		philo->s_fork = &philo->main_data->forks[idx];
	}
}

/**
 * Norminette Bypass.
 * Allocate memory for philos and initialize them and their mutexes,
 * except for their threads (they're not getting started yet)
 * and their last meal time.
 * @warning	Forks in \p out must be initialized before calling this function!
 * @param	out	Where to save philos.
 * @return	-1, if something went wrong;
 * 			Some non-negative value, if everything went ok.
 */
static int	ft_init_philos_except_for_threads_and_time(struct s_data *out)
{
	int	i;
	int	j;

	i = 0;
	out->philos = malloc((long unsigned int)(out
				->args.num_of_philos) * sizeof(struct s_philo));
	if (out->philos == NULL)
		return (-1);
	while (i < out->args.num_of_philos)
	{
		out->philos[i].id = i + 1;
		if (pthread_mutex_init(&out->philos[i].meal_lock, NULL) == -1)
		{
			j = 0;
			while (j < i)
				(void)pthread_mutex_destroy(&out->philos[j++].meal_lock);
			return (free(out->philos), out->philos = NULL, -1);
		}
		out->philos[i].main_data = out;
		ft_philo_set_forks(&out->philos[i]);
		i++;
	}
	return (0);
}

int	ft_init_everything_except_for_threads_and_time(struct s_data *out)
{
	int	i;

	if (pthread_mutex_init(&out->finish_lock, NULL) == -1)
		return (-1);
	else if (ft_init_forks(out) == -1)
		return ((void)pthread_mutex_destroy(&out->finish_lock), -1);
	else if (ft_init_philos_except_for_threads_and_time(out) == -1)
	{
		i = 0;
		while (i < out->args.num_of_philos)
			(void)pthread_mutex_destroy(&out->forks[i++]);
		return ((void)pthread_mutex_destroy(&out->finish_lock),
			free(out->forks), out->forks = NULL, -1);
	}
	return (0);
}
