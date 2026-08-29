/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 17:00:47 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/29 17:56:43 by lrouchon         ###   ########.fr       */
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
