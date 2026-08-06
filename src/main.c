/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 15:55:35 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/06 18:21:43 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timer(void)
{
	static long long	start_time_ms;
	struct timeval		tv;

	if (!start_time_ms)
	{
		gettimeofday(&tv, NULL);
		start_time_ms = tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;
	}
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL + tv.tv_usec / 1000LL) - start_time_ms);
}

void	error(char *str)
{
	printf("ERROR: %s", str);
}

int	main(int argc, const char **argv)
{
	t_times			*times;
	t_philosopher	*table;
	t_philosopher	*head;
	int				i;

	if (argc < 5)
		return (error("not enough arguments"), EXIT_FAILURE);
	times = init_times(argv);
	if (!times)
		return (error("couldn't initialize times struct"), EXIT_FAILURE);
	table = init_table(argv, times);
	if (!table)
		return (free(times), error("couldn't initialize table"), EXIT_FAILURE);
	timer();
	print_table(table);
	head = table;
	i = times->philosopher_amount;
	while (i > 0)
	{
		pthread_create(&table->thread, NULL, live, table);
		table = table->next;
		i--;
	}
	table = head;
	i = times->philosopher_amount;
	while (i > 0)
	{
		pthread_join(table->thread, NULL);
		table = table->next;
		i--;
	}
	// clear_table(&table);
	free(times);
	return (EXIT_SUCCESS);
}
