/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_and_defines.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:56:23 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 00:52:03 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_AND_DEFINES_H
# define STRUCTS_AND_DEFINES_H

# include <pthread.h>
# include <stdbool.h>

/**
 * ---------------------------------------------------------------------------
 * Constants.
 * ---------------------------------------------------------------------------
 */
/* To check argument count. */
# define ARGS_WO_CYCLES	5
# define ARGS_W_CYCLES	6

/* For error logging. */
# define APP_NAME				"philo"
# define BAD_ARG_COUNT_MSG		"Invalid usage."
# define EMPTY_ARG_MSG			"Some argument is empty."
# define INVALID_ARG_MSG		"Some argument isn't a number or overflows."
# define ARG_IS_NEGATIVE_MSG	"Some argument is negative."
# define ZERO_PHILOSOPHERS_MSG	"Number of philosophers can't be 0."
# define GETTIMEOFDAY_FAIL_MSG	"gettimeofday() failed."

/**
 * ---------------------------------------------------------------------------
 * Structures.
 * ---------------------------------------------------------------------------
 */
/* About time frames: it's not written in the subject,
 * that time_to_die, time_to_eat or time_to_sleep can't be 0.
 * So we treat 0 time frames as valid. */
struct s_args
{
	int	num_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	cycles;			/* -1 == not initialized. */
};

/* We can basically treat philo as an object. Well, that's his body! */
struct s_philo
{
	pthread_t		thread;
	int				id;				/* For output (logging) increase by 1. */
	long			last_meal;		/* Time of last meal in milliseconds. */
	pthread_mutex_t	meal_lock;		/* \ref last_meal is a critical section. */
	int				meals_eaten;
	struct s_data	*main_data;
};

/* Subject doesn't mention that watchdog must be a thread.
 * However, if it must, we can easily achieve this. */
struct s_data
{
	struct s_args	args;
	struct s_philo	*philos;
	long			start_time;
	pthread_mutex_t	output_lock;
	pthread_mutex_t	*forks;
	bool			some_philo_died;
};

#endif	/* STRUCTS_AND_DEFINES_H */
