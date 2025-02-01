/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_and_defines.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:56:23 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/01 23:54:36 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_AND_DEFINES_H
# define STRUCTS_AND_DEFINES_H

/**
 * ---------------------------------------------------------------------------
 * Constants.
 * ---------------------------------------------------------------------------
 */
/* To check argument count. */
# define ARGS_WO_CYCLES	5
# define ARGS_W_CYCLES	6

/* For error logging. */
# define APP_NAME			"philo"
# define BAD_ARG_COUNT_MSG	"Invalid usage. Please see subject for details."
# define EMPTY_ARG_MSG		"Some argument is empty."
# define INVALID_ARG_MSG	"Some argument is not a number or overflows."

/**
 * ---------------------------------------------------------------------------
 * Structures.
 * ---------------------------------------------------------------------------
 */
struct s_args
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	cycles;			/* -1 == not initialized. */
};

#endif	/* STRUCTS_AND_DEFINES_H */
