/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 17:18:21 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/29 20:15:55 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	update_last_meal_time(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->last_meal_time = timer();
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
}

int	eat(t_philosopher *philosopher)
{
	if (is_dead(philosopher))
		return (release_forks(philosopher));
	update_last_meal_time(philosopher);
	print_lock(philosopher, "is eating", COLOR_YELLOW);
	ft_usleep(philosopher->times->time_to_eat, philosopher);
	print_lock(philosopher, "has finished eating", COLOR_YELLOW);
	release_forks(philosopher);
	return (1);
}

int	nap(t_philosopher *philosopher)
{
	if (is_dead(philosopher))
		return (0);
	print_lock(philosopher, "is sleeping", COLOR_BLUE);
	ft_usleep(philosopher->times->time_to_sleep, philosopher);
	print_lock(philosopher, "has finished sleeping", COLOR_BLUE);
	return (1);
}

int	think(t_philosopher *philosopher)
{
	if (is_dead(philosopher))
		return (0);
	print_lock(philosopher, "is thinking", COLOR_GREEN);
	return (1);
}

void	*lifecycle(void	*arg)
{
	t_philosopher	*philosopher;
	int				i;

	philosopher = (t_philosopher *)arg;
	starting_block(philosopher);
	i = 0;
	while (1)
	{
		if (!take_forks(philosopher))
			break ;
		if (!eat(philosopher))
			break ;
		i++;
		if (i == philosopher->times->eat_count)
			break ;
		if (!nap(philosopher))
			break ;
		if (!think(philosopher))
			break ;
	}
	pthread_mutex_lock(&philosopher->sync->finished_mutex);
	philosopher->sync->finished_count++;
	pthread_mutex_unlock(&philosopher->sync->finished_mutex);
	return (0);
}
