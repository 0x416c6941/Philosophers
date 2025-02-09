/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 14:49:03 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/03 02:34:13 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <routines.h>
#include <stdbool.h>
#include <structs_and_defines.h>
#include <pthread.h>
#include <stdio.h>
#include <time_stuff.h>

void	ft_log(struct s_philo *philo, enum e_log_what action)
{
	long	ms_timestamp;

	ms_timestamp = ft_get_current_ms() - philo->main_data->start_time;
	if (action == FORK || action == FORK_AND_EATING)
	{
		printf("%ld %d has taken a fork\n", ms_timestamp, philo->id);
		if (action == FORK_AND_EATING)
			printf("%ld %d is eating\n", ms_timestamp, philo->id);
	}
	else if (action == SLEEPING)
		printf("%ld %d is sleeping\n", ms_timestamp, philo->id);
	else if (action == THINKING)
		printf("%ld %d is thinking\n", ms_timestamp, philo->id);
	else if (action == DIED)
		printf("%ld %d died\n", ms_timestamp, philo->id);
}
