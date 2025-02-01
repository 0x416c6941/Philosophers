/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 00:50:00 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 00:53:56 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time_stuff.h>
#include <sys/time.h>
#include <utils.h>
#include <structs_and_defines.h>

#define MS_IN_SEC			1000
#define MICROSECONDS_IN_MS	1000

long	ft_get_current_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		ft_errmsg(GETTIMEOFDAY_FAIL_MSG, WITH_NEWLINE);
		return (0);
	}
	return (time.tv_sec * MS_IN_SEC + time.tv_usec / MICROSECONDS_IN_MS);
}

void	ft_usleep(long ms)
{
	const long	start = ft_get_current_ms();

	while (42)
		if ((ft_get_current_ms() - start) >= ms)
			break;
}
