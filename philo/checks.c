/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 17:00:47 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/29 19:58:59 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_dead(t_philosopher *philosopher)
{
	bool	dead;

	pthread_mutex_lock(&philosopher->sync->dead_mutex);
	dead = philosopher->sync->dead_flag;
	pthread_mutex_unlock(&philosopher->sync->dead_mutex);
	return (dead);
}

long long	get_last_meal_time(t_philosopher *philosopher)
{
	long long	last_meal_time;

	pthread_mutex_lock(&philosopher->last_meal_mutex);
	last_meal_time = philosopher->last_meal_time;
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	return (last_meal_time);
}

bool	is_all_finished(t_philosopher *philosopher)
{
	int	finished_count;

	pthread_mutex_lock(&philosopher->sync->finished_mutex);
	finished_count = philosopher->sync->finished_count;
	pthread_mutex_unlock(&philosopher->sync->finished_mutex);
	return (finished_count == philosopher->times->philosopher_amount);
}

bool	is_all_ready(t_philosopher *philosopher)
{
	int	ready_count;

	pthread_mutex_lock(&philosopher->sync->ready_mutex);
	ready_count = philosopher->sync->ready_count;
	pthread_mutex_unlock(&philosopher->sync->ready_mutex);
	return (ready_count == philosopher->times->philosopher_amount);
}

bool	has_started(t_philosopher *philosopher)
{
	bool	started;

	pthread_mutex_lock(&philosopher->started_mutex);
	started = philosopher->started;
	pthread_mutex_unlock(&philosopher->started_mutex);
	return (started);
}
