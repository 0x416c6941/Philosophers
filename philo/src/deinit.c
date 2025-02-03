/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 00:50:07 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/03 01:21:38 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <init.h>
#include <structs_and_defines.h>
#include <pthread.h>
#include <stdlib.h>
#include <stddef.h>

void	ft_deinit(struct s_data *data)
{
	int	i;

	i = 0;
	while (i < data->args.num_of_philos)
	{
		(void)pthread_join(data->philos[i].thread, NULL);
		(void)pthread_mutex_destroy(&data->philos[i].meal_lock);
		(void)pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->philos);
	data->philos = NULL;
	free(data->forks);
	data->forks = NULL;
	(void)pthread_mutex_destroy(&data->finish_lock);
}
