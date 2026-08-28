/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:04:58 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/28 17:15:05 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(
	t_philosopher *philosopher,
	pthread_mutex_t **first,
	pthread_mutex_t **second
)
{
	pthread_mutex_t	*tmp;

	if (*first > *second)
	{
		tmp = *first;
		*first = *second;
		*second = tmp;
	}
	pthread_mutex_lock(*first);
	if (is_dead(philosopher))
	{
		pthread_mutex_unlock(*first);
		return (1);
	}
	print_lock(philosopher, "has taken a fork");
	pthread_mutex_lock(*second);
	if (is_dead(philosopher))
	{
		pthread_mutex_unlock(*first);
		pthread_mutex_unlock(*second);
		return (1);
	}
	print_lock(philosopher, "has taken a fork");
	return (0);
}

int	take_forks_and_eat(t_philosopher *philosopher)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (is_dead(philosopher))
		return (1);
	first = &philosopher->fork->mutex;
	second = &philosopher->previous->fork->mutex;
	if (first == second || take_forks(philosopher, &first, &second) == 1)
		return (1);
	print_lock(philosopher, "is eating");
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->last_meal_time = timer();
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	ft_usleep(philosopher->times->time_to_eat, philosopher);
	print_lock(philosopher, "has finished eating");
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	return (0);
}

int	nap(t_philosopher *philosopher)
{
	if (is_dead(philosopher))
		return (1);
	print_lock(philosopher, "is sleeping");
	ft_usleep(philosopher->times->time_to_sleep, philosopher);
	print_lock(philosopher, "has finished sleeping");
	return (0);
}

bool	is_dead(t_philosopher *philosopher)
{
	bool	dead;

	pthread_mutex_lock(&philosopher->sync->state_mutex);
	dead = philosopher->sync->dead;
	pthread_mutex_unlock(&philosopher->sync->state_mutex);
	return (dead);
}

void	*lifecycle(void	*arg)
{
	t_philosopher	*philosopher;
	int				i;

	philosopher = (t_philosopher *)arg;
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->last_meal_time = timer();
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	i = 0;
	while (1)
	{
		if (take_forks_and_eat(philosopher))
			break ;
		if (nap(philosopher))
			break ;
		if (is_dead(philosopher))
			break ;
		print_lock(philosopher, "is thinking");
		i++;
		if (i == philosopher->times->times_eating)
			break ;
	}
	pthread_mutex_lock(&philosopher->sync->sync_mutex);
	philosopher->sync->ready_count++;
	pthread_mutex_unlock(&philosopher->sync->sync_mutex);
	return (0);
}
