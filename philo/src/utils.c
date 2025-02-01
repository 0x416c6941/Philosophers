/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:04:11 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/01 23:09:02 by asagymba         ###   ########.fr       */
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
