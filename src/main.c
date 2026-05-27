/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 15:55:35 by lrouchon          #+#    #+#             */
/*   Updated: 2026/05/27 19:05:01 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	timer(void)
{
	int				start_time;
	struct timeval	tv;

	start_time = gettimeofday(&tv, NULL);
	return (start_time);
}

void	error(char *str)
{
	printf("ERROR: %s", str);
}

int	main(int argc, const char **argv)
{
	t_times			*times;
	t_philosopher	*table;

	if (argc < 5)
		return (error("not enough arguments"), EXIT_FAILURE);
	times = init_times(argv);
	if (!times)
		return (error("couldn't initialize times struct"), EXIT_FAILURE);
	table = init_table(argv, times);
	if (!table)
		return (free(times), error("couldn't initialize table"), EXIT_FAILURE);
	print_table(table);
	// clear_table(&table);
	eat(table);
	free(times);
	return (EXIT_SUCCESS);
}
