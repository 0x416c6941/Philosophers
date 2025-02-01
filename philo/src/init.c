/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:38:21 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 00:03:54 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <init.h>
#include <utils.h>

int	ft_init_args(int argc, char *argv[], struct s_args *out)
{
	int	*current_out_field;
	int	read_arg;

	current_out_field = (int *)out;
	while (argc != 0)
	{
		if (ft_isspace(**argv))
			(*argv)++;
		if (**argv == '\0')
			return (ft_errmsg(EMPTY_ARG_MSG, WITH_NEWLINE), -1);
		else if (ft_atoi_modified((const char **)argv, &read_arg) == -1)
			return (ft_errmsg(INVALID_ARG_MSG, WITH_NEWLINE), -1);
		if (ft_isspace(**argv))
			(*argv)++;
		if (**argv != '\0')
			return (ft_errmsg(INVALID_ARG_MSG, WITH_NEWLINE), -1);
		*current_out_field++ = read_arg;
		argc--;
		argv++;
	}
	return (0);
}
