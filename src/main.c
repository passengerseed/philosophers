/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 15:55:35 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/18 18:32:04 by lrouchon         ###   ########.fr       */
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
	t_philosopher	*head;
	long long		last_meal;
	int				i;

	head = (t_philosopher *)arg;
	while (1)
	{
		pthread_mutex_lock(&head->sync->sync_mutex);
		if (head->sync->ready_count >= head->times->philosopher_amount)
		{
			pthread_mutex_unlock(&head->sync->sync_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&head->sync->sync_mutex);
		philosopher = head;
		i = 0;
		while (i < head->times->philosopher_amount)
		{
			pthread_mutex_lock(&philosopher->last_meal_mutex);
			last_meal = philosopher->last_meal_time;
			pthread_mutex_unlock(&philosopher->last_meal_mutex);
			if (!is_dead(philosopher) && timer() - last_meal >= philosopher->times->time_to_die)
			{
				pthread_mutex_lock(&philosopher->sync->state_mutex);
				philosopher->sync->dead = true;
				printf("[ %lld ms ]\t%s has died\n", timer(), philosopher->name);
				pthread_mutex_unlock(&philosopher->sync->state_mutex);
				return (NULL);
			}
			philosopher = philosopher->next;
			i++;
		}
		usleep(1000);
	}
	printf("SIMULATION FINISHED!");
	return (NULL);
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
	// print_table(table);
	head = table;
	i = times->philosopher_amount;
	while (i > 0)
	{
		usleep(1000);
		pthread_create(&table->thread, NULL, lifecycle, table);
		table = table->next;
		i--;
	}
	pthread_create(&panopticon, NULL, monitor, head);
	table = head;
	i = times->philosopher_amount;
	if (i == 1)
	{
		usleep(times->time_to_die * 1000);
		printf("[ %lld ms ]\t%s has died\n", timer(), head->name);
		pthread_join(head->thread, NULL);
		pthread_join(panopticon, NULL);
		clear_table(&table);
		return (EXIT_SUCCESS);
	}
	while (i > 0)
	{
		pthread_join(table->thread, NULL);
		table = table->next;
		i--;
	}
	pthread_join(panopticon, NULL);
	clear_table(&table);
	return (EXIT_SUCCESS);
}
