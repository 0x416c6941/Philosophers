/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:04:11 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 00:17:07 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <stddef.h>
#include <unistd.h>
#include <structs_and_defines.h>

size_t	ft_strlen(const char *s)
{
	size_t	ret;

	ret = 0;
	while (s[ret] != '\0')
		ret++;
	return (ret);
}

void	ft_errmsg(const char *msg, enum e_append_newline w_nl)
{
	if (write(STDERR_FILENO, APP_NAME, ft_strlen(APP_NAME)) == -1
		|| write(STDERR_FILENO, ": ", sizeof(": ") - 1) == -1
		|| write(STDERR_FILENO, msg, ft_strlen(msg)) == -1)
		return ;
	if (w_nl == WITH_NEWLINE)
		(void)write(STDERR_FILENO, "\n", sizeof("\n") - 1);
}

int	ft_isspace(int c)
{
	const char	*whitespace;

	whitespace = " \f\n\r\t\v";
	while (*whitespace != '\0')
	{
		if (*whitespace++ == c)
		{
			if (c != 0)
				return (c);
			return (1);
		}
	}
	return (0);
}

/* We assume that in the encoding system uses codes of numbers
 * between '0' and '9' are in sequence in ascending order. */
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		if (c != 0)
			return (c);
		return (1);
	}
	return (0);
}

/**
 * 1. As previously, we assume '0' and '9' are in sequence in ascending order.
 * 2. We're not afraid of overflows in our case, so we can just multiply
 * 	the result stored in \p out by -1.
 */
int	ft_atoi_modified(const char **nptr, int *out)
{
	int	sign;

	sign = 1;
	while (ft_isspace(**nptr))
		(*nptr)++;
	if (**nptr == '+' || **nptr == '-')
		if (*((*nptr)++) == '-')
			sign = -1;
	*out = 0;
	while (ft_isdigit(**nptr))
	{
		if ((*out * 10 + (**nptr - '0')) < *out)
			return (-1);
		*out = *out * 10 + (*((*nptr)++) - '0');
	}
	if (**nptr != '\0' && !ft_isspace(**nptr))
		return (-1);
	*out *= sign;
	return (0);
}
