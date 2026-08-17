/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 15:55:35 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/17 17:41:21 by lrouchon         ###   ########.fr       */
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

void	*monitor(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	while (1)
	{
		pthread_mutex_lock(&philosopher->sync->sync_mutex);
		if (philosopher->sync->ready_count == philosopher->times->philosopher_amount)
			break ;
		pthread_mutex_unlock(&philosopher->sync->sync_mutex);
		pthread_mutex_lock(&philosopher->last_meal_mutex);
		if (timer() - philosopher->last_meal_time >= philosopher->times->time_to_die)
		{
			printf("[ %lld ms ]	%s has died!\n", timer(), philosopher->name);
			exit(EXIT_FAILURE);
		}
		pthread_mutex_unlock(&philosopher->last_meal_mutex);

	}
	printf("SIMULATION FINISHED!");
	return (0);
}

int	main(int argc, const char **argv)
{
	t_times			*times;
	t_philosopher	*table;
	t_philosopher	*head;
	pthread_t		panopticon;
	int				i;

	if (argc < 5)
		return (error("not enough arguments"), EXIT_FAILURE);
	times = init_times(argc, argv);
	if (!times)
		return (error("couldn't initialize times struct"), EXIT_FAILURE);
	table = init_table(argv, times);
	if (!table)
		return (free(times), error("couldn't initialize table"), EXIT_FAILURE);
	print_table(table);
	head = table;
	i = times->philosopher_amount;
	while (i > 0)
	{
		// usleep(1000 * (times->philosopher_amount - i));
		pthread_create(&table->thread, NULL, lifecycle, table);
		table = table->next;
		i--;
	}
	panopticon = pthread_create(&panopticon, NULL, monitor, table);
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
