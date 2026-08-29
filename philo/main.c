/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 17:06:18 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/29 18:38:29 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	monitor_loop(t_philosopher *philosopher)
{
	int			i;

	i = 0;
	while (i < philosopher->times->philosopher_amount)
	{
		if (!is_dead(philosopher) && timer() - get_last_meal_time(philosopher)
			>= philosopher->times->time_to_die)
		{
			pthread_mutex_lock(&philosopher->sync->dead_mutex);
			philosopher->sync->dead_flag = true;
			printf("[ %lld ms ]\t%s has died\n", timer(), philosopher->name);
			pthread_mutex_unlock(&philosopher->sync->dead_mutex);
			return (0);
		}
		philosopher = philosopher->next;
		i++;
	}
	return (1);
}

void	*monitor(void *arg)
{
	t_philosopher	*philosopher;
	t_philosopher	*head;

	head = (t_philosopher *)arg;
	while (1)
	{
		if (is_all_finished(head))
			return (NULL);
		philosopher = head;
		if (!monitor_loop(philosopher))
			return (NULL);
		usleep(1000);
	}
	printf("SIMULATION FINISHED!");
	return (NULL);
}

void	lone_philosopher(t_philosopher *philosopher)
{
	usleep(philosopher->times->time_to_die * 1000);
	print_lock(philosopher, "died");
}

int	main(int argc, const char **argv)
{
	t_times			*times;
	t_philosopher	*table;
	t_philosopher	*head;
	pthread_t		panopticon;
	int				i;

	if (argc < 5)
		return (printf("not enough arguments"), EXIT_FAILURE);
	times = init_times(argc, argv);
	if (!times)
		return (printf("couldn't initialize times struct"), EXIT_FAILURE);
	table = init_table(argv, times);
	if (!table)
		return (free(times), printf("couldn't initialize table"), EXIT_FAILURE);
	i = times->philosopher_amount;
	if (i != 1)
	{
		head = table;
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
		while (i > 0)
		{
			pthread_join(table->thread, NULL);
			table = table->next;
			i--;
		}
		pthread_join(panopticon, NULL);
	}
	else
		lone_philosopher(table);
	clear_table(&table, 0);
	return (EXIT_SUCCESS);
}

//TODO: add ready check at start
