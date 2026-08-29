/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 17:41:16 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/29 18:32:51 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	lock_fork(t_philosopher *philosopher, t_fork *fork)
{
	if (is_dead(philosopher))
		return (0);
	pthread_mutex_lock(&fork->fork_mutex);
	return (1);
}

int	take_forks(t_philosopher *philosopher)
{
	if (philosopher->index % 2 == 0)
	{
		if (!lock_fork(philosopher, philosopher->previous->fork))
			return (0);
		if (!lock_fork(philosopher, philosopher->fork))
			return (0);
	}
	else
	{
		if (!lock_fork(philosopher, philosopher->fork))
			return (0);
		if (!lock_fork(philosopher, philosopher->previous->fork))
			return (0);
	}
	return (1);
}

int	release_forks(t_philosopher *philosopher)
{
	if (philosopher->index % 2 == 0)
	{
		pthread_mutex_unlock(&philosopher->previous->fork->fork_mutex);
		pthread_mutex_unlock(&philosopher->fork->fork_mutex);
	}
	else
	{
		pthread_mutex_unlock(&philosopher->fork->fork_mutex);
		pthread_mutex_unlock(&philosopher->previous->fork->fork_mutex);
	}
	return (1);
}
