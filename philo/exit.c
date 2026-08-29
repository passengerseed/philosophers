/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 17:16:12 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/29 19:58:49 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clear_philosopher(
	int count,
	t_philosopher *philosopher
	)
{
	t_philosopher	*tmp;
	int				i;

	i = 0;
	while (i < count)
	{
		tmp = philosopher->next;
		pthread_mutex_destroy(&philosopher->last_meal_mutex);
		pthread_mutex_destroy(&philosopher->started_mutex);
		pthread_mutex_destroy(&philosopher->fork->fork_mutex);
		free(philosopher->name);
		free(philosopher->fork);
		free(philosopher);
		philosopher = tmp;
		i++;
	}
}

void	clear_table(t_philosopher **table)
{
	t_philosopher	*philosopher;
	t_times			*times;
	t_sync			*sync;
	int				count;

	if (!table || !*table)
		return ;
	philosopher = *table;
	count = philosopher->times->philosopher_amount;
	times = philosopher->times;
	sync = philosopher->sync;
	clear_philosopher(count, philosopher);
	free(times);
	pthread_mutex_destroy(&sync->print_mutex);
	pthread_mutex_destroy(&sync->dead_mutex);
	pthread_mutex_destroy(&sync->ready_mutex);
	pthread_mutex_destroy(&sync->finished_mutex);
	free(sync);
	*table = NULL;
}
