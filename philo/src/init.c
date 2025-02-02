/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:38:21 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 01:23:32 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <init.h>
#include <structs_and_defines.h>
#include <utils.h>
#include <stdbool.h>
#include <time_stuff.h>
#include <stdlib.h>
#include <stddef.h>

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
 * Allocate memory for philos and initialize them and their mutexes.
 * @param	out	Where to save philos.
 * @return	-1, if something went wrong;
 * 			Some non-negative value, if everything went ok.
 */
static int	ft_init_philos(struct s_data *out)
{
	int	i;
	int	j;

	i = 0;
	out->philos = (struct s_philo *)malloc(
			(long unsigned int)out->args.num_of_philos
			* sizeof(struct s_philo));
	if (out->philos == NULL)
		return (-1);
	while (i < out->args.num_of_philos)
	{
		out->philos[i].id = i;
		out->philos[i].last_meal = out->start_time;
		if (pthread_mutex_init(&out->philos[i].meal_lock, NULL) == -1)
		{
			j = 0;
			while (j < i)
				(void)pthread_mutex_destroy(&out->philos[j++].meal_lock);
			return (free(out->philos), out->philos = NULL, -1);
		}
		out->philos[i].meals_eaten = 0;
		out->philos[i++].main_data = out;
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

	out->forks = (pthread_mutex_t *)malloc(
			(long unsigned int)out->args.num_of_philos
			* sizeof(pthread_mutex_t));
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

int	ft_init_everything_else(struct s_data *out)
{
	int	i;

	out->start_time = ft_get_current_ms();
	if (ft_init_philos(out) == -1)
		return (-1);
	else if (pthread_mutex_init(&out->output_lock, NULL) == -1)
	{
		i = 0;
		while (i < out->args.num_of_philos)
			(void)pthread_mutex_destroy(&out->philos[i++].meal_lock);
		return (free(out->philos), out->philos = NULL, -1);
	}
	else if (ft_init_forks(out) == -1)
	{
		i = 0;
		while (i < out->args.num_of_philos)
			(void)pthread_mutex_destroy(&out->philos[i++].meal_lock);
		return (free(out->philos), out->philos = NULL,
			(void)pthread_mutex_destroy(&out->output_lock), -1);
	}
	return (0);
}
