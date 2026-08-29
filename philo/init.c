/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 16:49:18 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/29 18:37:34 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_times	*init_times(
	int argc,
	const char **argv
	)
{
	t_times	*new_times;
	int		i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) < 0)
			return (NULL);
		i++;
	}
	new_times = malloc(sizeof(t_times));
	if (!new_times)
		return (NULL);
	new_times->philosopher_amount = ft_atoi(argv[1]);
	new_times->time_to_die = ft_atoi(argv[2]);
	new_times->time_to_eat = ft_atoi(argv[3]);
	new_times->time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		new_times->eat_count = ft_atoi(argv[5]);
	else
		new_times->eat_count = 0;
	return (new_times);
}

t_philosopher	*init_philosopher(
	t_times *times,
	t_sync *sync,
	int index
)
{
	t_philosopher	*new_philosopher;
	t_fork			*new_fork;

	new_philosopher = malloc(sizeof(t_philosopher));
	if (!new_philosopher)
		return (NULL);
	new_fork = malloc(sizeof(t_fork));
	if (!new_fork)
		return (free(new_philosopher), NULL);
	pthread_mutex_init(&new_fork->fork_mutex, NULL);
	pthread_mutex_init(&new_philosopher->last_meal_mutex, NULL);
	new_philosopher->thread = 0;
	new_philosopher->name = ft_itoa(index + 1);
	new_philosopher->index = index;
	new_philosopher->times = times;
	new_philosopher->sync = sync;
	new_philosopher->fork = new_fork;
	new_philosopher->next = NULL;
	new_philosopher->previous = NULL;
	return (new_philosopher);
}

t_sync	*init_sync(void)
{
	t_sync			*new_sync;

	new_sync = malloc(sizeof(t_sync));
	pthread_mutex_init(&new_sync->print_mutex, NULL);
	pthread_mutex_init(&new_sync->dead_mutex, NULL);
	new_sync->dead_flag = false;
	new_sync->finished_count = 0;
	return (new_sync);
}

t_philosopher	*init_table(
	const char **argv,
	t_times *times
)
{
	t_philosopher	*new_table;
	t_philosopher	*last;
	t_sync			*sync;
	int				i;
	int				count;

	new_table = NULL;
	sync = init_sync();
	count = ft_atoi(argv[1]);
	i = -1;
	while (++i < count)
		table_add_back(&new_table, init_philosopher(times, sync, i));
	if (!new_table)
		return (NULL);
	last = table_last(new_table);
	last->next = new_table;
	new_table->previous = last;
	return (new_table);
}
