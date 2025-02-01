/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:58:15 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/01 23:05:25 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

/**
 * ---------------------------------------------------------------------------
 * Enumerations.
 * ---------------------------------------------------------------------------
 */
enum e_append_newline
{
	NO_NEWLINE,
	WITH_NEWLINE
};

/**
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */
size_t	ft_strlen(const char *s);

/**
 * Prints \p msg to stderr with the app's name as prefix.
 * @param	msg		Message to log.
 * @param	w_nl	If should append newline after the message.
 */
void	ft_errmsg(const char *msg, enum e_append_newline w_nl);

#endif	/* UTILS_H */
