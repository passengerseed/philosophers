/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:04:58 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/14 19:15:06 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philosopher *philosopher)
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
	philosopher->ready_to_eat = true;
}

int	eat(t_philosopher *philosopher)
{
	int				status;
	__useconds_t	time;

	time = philosopher->times->time_to_eat * 1000;
	philosopher->state = EATING;
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->last_meal_time = timer();
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	printf("[ %lld ms ]%s	%s is eating%s\n", timer(), COLOR_YELLOW, philosopher->name, COLOR_RESET);
	status = usleep(time);
	printf("[ %lld ms ]%s	%s is done eating!%s\n", timer(), COLOR_YELLOW, philosopher->name, COLOR_RESET);
	return (status);
}

int	nap(t_philosopher *philosopher)
{
	int				status;
	__useconds_t	time;

	time = philosopher->times->time_to_sleep * 1000;
	printf("[ %lld ms ]%s	%s is sleeping%s\n", timer(), COLOR_BLUE, philosopher->name, COLOR_RESET);
	status = usleep(time);
	printf("[ %lld ms ]%s	%s is done sleeping!%s\n", timer(), COLOR_BLUE, philosopher->name, COLOR_RESET);
	return (status);
}

void	die(t_philosopher *philosopher)
{
	printf("[ %lld ms ]%s	%s has died!%s\n", timer(), COLOR_RED, philosopher->name, COLOR_RESET);
	exit(EXIT_SUCCESS);
}

void	wait_for_phase(t_sync *sync, int philosopher_index)
{
	pthread_mutex_lock(&sync->sync_mutex);
	while (1)
	{
		if (philosopher_index % 2 == 0 && sync->even_phase_ready)
		{
			pthread_mutex_unlock(&sync->sync_mutex);
			return ;
		}
		if (philosopher_index % 2 != 0 && sync->odd_phase_ready)
		{
			pthread_mutex_unlock(&sync->sync_mutex);
			return ;
		}
		pthread_mutex_unlock(&sync->sync_mutex);
		usleep(1000);
		pthread_mutex_lock(&sync->sync_mutex);
	}
}

void	start_phase(t_sync *sync, int philosopher_index)
{
	pthread_mutex_lock(&sync->sync_mutex);
	if (philosopher_index % 2 == 0)
	{
		sync->even_ready_count++;
		if (sync->even_ready_count == sync->even_total)
			sync->even_phase_ready = true;
	}
	else
	{
		sync->odd_ready_count++;
		if (sync->odd_ready_count == sync->odd_total)
			sync->odd_phase_ready = true;
	}
	pthread_mutex_unlock(&sync->sync_mutex);
}

void	*live(void *arg)
{
	t_philosopher	*philosopher;
	int				i;

	philosopher = (t_philosopher *)arg;
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->last_meal_time = timer();
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	start_phase(philosopher->sync, philosopher->index);
	wait_for_phase(philosopher->sync, philosopher->index);
	i = 0;
	while (i < philosopher->times->times_eating)
	{
		if (philosopher->state == THINKING)
		{
			take_forks(philosopher);
			eat(philosopher);
		}
		if (philosopher->state == EATING)
		{
			i++;
			nap(philosopher);
		}
		if (philosopher->state == SLEEPING)
			printf("[ %lld ms ]%s	%s is thinking%s\n", timer(), COLOR_RESET, philosopher->name, COLOR_RESET);
	}
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->finished = true;
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	return (NULL);
}
