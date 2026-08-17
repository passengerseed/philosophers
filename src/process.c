/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:04:58 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/17 17:58:37 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks_and_eat(t_philosopher *philosopher)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	pthread_mutex_t	*tmp;

	first = &philosopher->fork->mutex;
	second = &philosopher->previous->fork->mutex;
	tmp = NULL;
	if (first > second)
	{
		tmp = first;
		first = second;
		second = tmp;
	}
	pthread_mutex_lock(first);
	printf("[ %lld ms ]	%s has taken a fork\n", timer(), philosopher->name);
	pthread_mutex_lock(second);
	printf("[ %lld ms ]	%s has taken a fork\n", timer(), philosopher->name);
	printf("[ %lld ms ]	%s is eating\n", timer(), philosopher->name);
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->last_meal_time = timer();
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	usleep(philosopher->times->time_to_eat * 1000);
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->last_meal_time = timer();
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	printf("[ %lld ms ]	%s has finished eating\n", timer(), philosopher->name);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	return (0);
}

int	nap(t_philosopher *philosopher)
{
	printf("[ %lld ms ]	%s is sleeping\n", timer(), philosopher->name);
	usleep(philosopher->times->time_to_sleep * 1000);
	printf("[ %lld ms ]	%s has finished sleeping\n", timer(), philosopher->name);
	return (0);
}

void	*lifecycle(void	*arg)
{
	t_philosopher	*philosopher;
	int				i;

	philosopher = (t_philosopher *)arg;
	i = 0;
	while (1)
	{
		take_forks_and_eat(philosopher);
		nap(philosopher);
		printf("[ %lld ms ]	%s is thinking\n", timer(), philosopher->name);
		i++;
		if (i == philosopher->times->times_eating)
			break ;
	}
	pthread_mutex_lock(&philosopher->sync->sync_mutex);
	philosopher->sync->ready_count++;
	pthread_mutex_unlock(&philosopher->sync->sync_mutex);
	return (0);
}
