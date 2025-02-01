/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:38:21 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 00:27:16 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <init.h>
#include <structs_and_defines.h>
#include <utils.h>
#include <stdbool.h>

int	ft_init_args(int argc, char *argv[], struct s_args *out)
{
	int	*current_out_field;
	int	read_arg;

	current_out_field = (int *)out;
	while (argc != 0)
	{
		while (ft_isspace(**argv))
			(*argv)++;
		if (**argv == '\0')
			return (ft_errmsg(EMPTY_ARG_MSG, WITH_NEWLINE), -1);
		else if (ft_atoi_modified((const char **)argv, &read_arg) == -1)
			return (ft_errmsg(INVALID_ARG_MSG, WITH_NEWLINE), -1);
		if (!(read_arg >= 0))
			return (ft_errmsg(ARG_IS_NEGATIVE_MSG, WITH_NEWLINE), -1);
		while (ft_isspace(**argv))
			(*argv)++;
		if (**argv != '\0')
			return (ft_errmsg(INVALID_ARG_MSG, WITH_NEWLINE), -1);
		*current_out_field++ = read_arg;
		argc--;
		argv++;
	}
	return (0);
}
