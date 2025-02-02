/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 01:51:24 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 02:04:37 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <routines.h>
#include <structs_and_defines.h>
#include <pthread.h>

pthread_mutex_t	*ft_get_first_fork(struct s_philo *data)
{
	if ((data->id % 2) == 0)
		return (&data->main_data->forks[data->id]);
	else
	{
		if (data->id == 0)
			return (&data->main_data->forks[data->main_data->args.num_of_philos
					- 1]);
		return (&data->main_data->forks[data->id - 1]);
	}
}

pthread_mutex_t	*ft_get_second_fork(struct s_philo *data)
{
	if ((data->id % 2) == 0)
	{
		if (data->id == 0)
			return (&data->main_data->forks[data->main_data->args.num_of_philos
					- 1]);
		return (&data->main_data->forks[data->id - 1]);
	}
	return (&data->main_data->forks[data->id]);
}
