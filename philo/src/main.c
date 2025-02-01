/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asagymba <asagymba@student.42prague.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:46:33 by asagymba          #+#    #+#             */
/*   Updated: 2025/02/01 23:08:50 by asagymba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <structs_and_defines.h>
#include <utils.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (!(argc == ARGS_WO_CYCLES || argc == ARGS_W_CYCLES))
		return (ft_errmsg(BAD_ARG_COUNT_MSG, WITH_NEWLINE), EXIT_FAILURE);
	(void)argv;
	return (0);
}
