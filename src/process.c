/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:04:58 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/17 17:02:48 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


// printf("[ %lld ms ]	%s has taken a fork\n", timer(), philosopher->name);

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
	pthread_mutex_lock(&philosopher->times->times_mutex);
	usleep(philosopher->times->time_to_eat * 1000);
	pthread_mutex_unlock(&philosopher->times->times_mutex);
	printf("[ %lld ms ]	%s has finished eating\n", timer(), philosopher->name);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	return (0);
}

int	nap(t_philosopher *philosopher)
{
	printf("[ %lld ms ]	%s is sleeping\n", timer(), philosopher->name);
	pthread_mutex_lock(&philosopher->times->times_mutex);
	usleep(philosopher->times->time_to_sleep * 1000);
	pthread_mutex_unlock(&philosopher->times->times_mutex);
	printf("[ %lld ms ]	%s has finished sleeping\n", timer(), philosopher->name);
	return (0);
}

void	*lifecycle(void	*arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	take_forks_and_eat(philosopher);
	nap(philosopher);
	printf("[ %lld ms ]	%s is thinking\n", timer(), philosopher->name);
	return (0);
}
