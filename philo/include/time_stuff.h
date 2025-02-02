/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_stuff.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 00:46:04 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 15:14:23 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_STUFF_H
# define TIME_STUFF_H

/**
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */
/**
 * Gets current time in milliseconds.
 * If gettimeofday() syscall fails, error will be logged.
 * @return	Current time in milliseconds;
 * 			0 if gettimeofday() syscall failed.
 */
long	ft_get_current_ms(void);

/**
 * Sleep until \p ms.
 * @param	ms	Until how many milliseconds (in time) to sleep.
 */
void	ft_wait_until(long ms);

/**
 * Faster version of usleep() syscall,
 * however can handle only milliseconds (and not microseconds).
 * @param	ms	Milliseconds to sleep for.
 */
void	ft_usleep(long ms);

#endif	/* TIME_STUFF_H */
