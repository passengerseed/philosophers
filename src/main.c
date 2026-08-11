/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 15:55:35 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/11 19:02:01 by lrouchon         ###   ########.fr       */
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

void	death_clock(
	t_philosopher *philosopher,
	int delay
)
{
	long long			start_time_ms;
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	start_time_ms = tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;
	while (((tv.tv_sec * 1000LL + tv.tv_usec / 1000LL) - start_time_ms) < (long long)delay)
	{
		gettimeofday(&tv, NULL);
		if (philosopher->state == EATING)
			return ;
	}

	switch_states(philosopher, DEAD, tv.tv_sec * 1000LL + tv.tv_usec / 1000LL);
}

void	panopticon(
	t_philosopher *philosopher,
	const char **argv
)
{
	int	finished_count;
	int	count;
	int	i;
	
	count = ft_atoi(argv[1]);
	while (philosopher)
	{
		finished_count = 0;
		i = 0;
		while (i <= count)
		{
			pthread_mutex_lock(&philosopher->last_meal_mutex);
			if (((timer() - philosopher->last_meal_time)
					> philosopher->times->time_to_die)
				&& philosopher->state != EATING)
				switch_states(philosopher, DEAD, timer());
			if (philosopher->finished == true)
				finished_count++;
			pthread_mutex_unlock(&philosopher->last_meal_mutex);
			philosopher = philosopher->next;
			i++;
		}
		if (finished_count == count)
			return ;
	}
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
	times = init_times(argc, argv);
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
		// usleep(1000 * (times->philosopher_amount - i));
		pthread_create(&table->thread, NULL, live, table);
		table = table->next;
		i--;
	}
	table = head;
	i = times->philosopher_amount;
	panopticon(table, argv);
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
