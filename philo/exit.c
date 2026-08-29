/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 17:16:12 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/29 17:17:41 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clear_table(
	t_philosopher **table,
	int i
)
{
	t_philosopher	*philosopher;
	t_philosopher	*tmp;
	t_times			*times;
	t_sync			*sync;
	int				count;

	if (!table || !*table)
		return ;
	philosopher = *table;
	count = philosopher->times->philosopher_amount;
	times = philosopher->times;
	sync = philosopher->sync;
	i = 0;
	while (i < count)
	{
		tmp = philosopher->next;
		pthread_mutex_destroy(&philosopher->last_meal_mutex);
		pthread_mutex_destroy(&philosopher->fork->fork_mutex);
		free(philosopher->name);
		free(philosopher->fork);
		free(philosopher);
		philosopher = tmp;
		i++;
	}
	free(times);
	pthread_mutex_destroy(&sync->print_mutex);
	pthread_mutex_destroy(&sync->dead_mutex);
	free(sync);
	*table = NULL;
}
