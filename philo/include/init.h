/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:30:32 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 14:25:58 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <structs_and_defines.h>

/**
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */
/**
 * Reads all arguments from \p argv and stores them in \p out.
 * If some error is encountered, error message is logged to stderr.
 * @warning	Implmentation assumes all fields in \p out are of size sizeof(int).
 * @warning	Pointers in \p argv might change their positions.
 * @warning	String in \p argv can't contain multiple arguments,
 * 			we consider that to be an error (thanks Norminette!).
 * @warning	It's up to you to make sure we don't overrun the buffer in \p out.
 * @param	argc	Argument count (excluding usual argv[0]).
 * @param	argv	Argument vector (excluding usual argv[0]).
 * @param	out		Where to save the read arguments.
 * @return	-1, if something went wrong;
 * 			Some non-negative value, if all arguments are ok.
 */
int		ft_init_args(int argc, char *argv[], struct s_args *out);

/**
 * Initializes everything except for threads (doesn't start philos),
 * starting time of a program and last meal time of a philo.
 * @param	out	Where to save the initialized stuff.
 * @return	-1, if something went wrong;
 * 			Some non-negative value, if everything went ok.
 */
int		ft_init_everything_except_for_threads_and_time(struct s_data *out);

/**
 * Wait for all philos to stop running, and clear all allocated memory.
 * @param	data	Data to deallocate.
 */
void	ft_deinit(struct s_data *data);

#endif	/* INIT_H */
