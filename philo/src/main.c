/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:46:33 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 03:00:02 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structs_and_defines.h>
#include <utils.h>
#include <stdlib.h>
#include <string.h>
#include <init.h>
#include <time_stuff.h>
#include <pthread.h>
#include <routines.h>

/**
 * philo.
 * @warning	Since we don't have exit() available
 * 			(and since I dislike Norminette),
 * 			return value of pthread_create() is ignored.
 * @param	data	Program's data.
 */
static void	ft_philo(struct s_data *data)
{
	int		i;

	data->start_time = ft_get_current_ms();
	i = 0;
	while (i < data->args.num_of_philos)
	{
		data->philos[i].last_meal = data->start_time;
		(void)pthread_create(&data->philos[i].thread, NULL,
			(void *(*)(void *))ft_philo_routine, &data->philos[i]);
		i++;
	}
	(void)ft_watchdog_routine(data);
}

int	main(int argc, char *argv[])
{
	struct s_data	data;

	if (!(argc == ARGS_WO_CYCLES || argc == ARGS_W_CYCLES))
		return (ft_errmsg(BAD_ARG_COUNT_MSG, WITH_NEWLINE), EXIT_FAILURE);
	(void)memset(&data, 0, sizeof(data));
	data.args.cycles = -1;
	if (ft_init_args(--argc, ++argv, &data.args) == -1)
		return (EXIT_FAILURE);
	else if (data.args.num_of_philos == 0)
		return (ft_errmsg(ZERO_PHILOSOPHERS_MSG, WITH_NEWLINE), EXIT_FAILURE);
	else if (ft_init_everything_else(&data) == -1)
		return (ft_errmsg(MALLOC_FAIL_MSG, WITH_NEWLINE), EXIT_FAILURE);
	ft_philo(&data);
	ft_deinit(&data);
	return (0);
}
