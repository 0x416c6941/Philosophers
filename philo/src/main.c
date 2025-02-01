/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:46:33 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/02 00:04:29 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structs_and_defines.h>
#include <utils.h>
#include <stdlib.h>
#include <string.h>
#include <init.h>

int	main(int argc, char *argv[])
{
	struct s_args	args;

	if (!(argc == ARGS_WO_CYCLES || argc == ARGS_W_CYCLES))
		return (ft_errmsg(BAD_ARG_COUNT_MSG, WITH_NEWLINE), EXIT_FAILURE);
	(void)memset(&args, 0, sizeof(args));
	if (ft_init_args(--argc, ++argv, &args) == -1)
		return (EXIT_FAILURE);
	return (0);
}
