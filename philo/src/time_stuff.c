/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 00:50:00 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/03 01:40:50 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time_stuff.h>
#include <sys/time.h>
#include <utils.h>
#include <structs_and_defines.h>
#include <unistd.h>

#define MS_IN_SEC			1000
#define MICROSECONDS_IN_MS	1000

/* In microseconds. See usleep(3). */
#define FT_USLEEP_SUSPEND_EXECUTION	100

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

/* pthread_cond_broadcast() is forbidden.
 * Sad. We need to rely on this dirty hack instead. */
void	ft_wait_until(long ms)
{
	while (ft_get_current_ms() < ms)
		;
}

/* usleep() syscall actually suspends the execution
 * of a block of code for the specified amount of seconds.
 * When we use multiple threads on an actual physical CPU thread,
 * it proves to be REALLY handy. */
void	ft_usleep(long ms)
{
	const long	start = ft_get_current_ms();

	while ((ft_get_current_ms() - start) < ms)
		usleep(FT_USLEEP_SUSPEND_EXECUTION);
}
