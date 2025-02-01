/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:58:15 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/01 23:29:16 by asagymba         ###   ########.fr       */
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

int		ft_isspace(int c);
int		ft_isdigit(int c);

/**
 * A modified version of atoi(). Skips all whitespaces, '+' and '-' signs
 * and all numbers in \p nptr during the number conversion.
 * @param	nptr	Number string.
 * @param	out		Where to store the converted number.
 * @return	-1, if encountered overflow or a number;
 * 			Some non-negative value, if everything went fine.
 */
int		ft_atoi_modified(const char **nptr, int *out);

#endif	/* UTILS_H */
