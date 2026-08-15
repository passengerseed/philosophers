/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:04:58 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/15 18:54:03 by lrouchon         ###   ########.fr       */
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
	pthread_mutex_unlock(&philosopher->fork->mutex);
	pthread_mutex_unlock(&philosopher->previous->fork->mutex);
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
	while (1)
	{
		pthread_mutex_lock(&sync->sync_mutex);
		if (philosopher_index % 2 == 0)
		{
			if (sync->even_ready_count == sync->even_total)
			{
				sync->even_ready_count = 0;
				sync->even_phase_ready = false;
				pthread_mutex_unlock(&sync->sync_mutex);
				return ;
			}

		}
		else
		{
			if (sync->odd_ready_count == sync->odd_total)
			{
				sync->odd_ready_count = 0;
				sync->odd_phase_ready = false;
				pthread_mutex_unlock(&sync->sync_mutex);
				return ;
			}

		}
		pthread_mutex_unlock(&sync->sync_mutex);
		usleep(1000);
	}
}

void	start_phase(t_sync *sync, int philosopher_index)
{
	pthread_mutex_lock(&sync->sync_mutex);
	if (philosopher_index % 2 == 0)
		sync->even_ready_count++;
	else
		sync->odd_ready_count++;
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
	i = 0;
	while (i < philosopher->times->times_eating)
	{
		start_phase(philosopher->sync, philosopher->index);
		wait_for_phase(philosopher->sync, philosopher->index);

		pthread_mutex_lock(&philosopher->state_mutex);
		philosopher->state = THINKING;
		pthread_mutex_unlock(&philosopher->state_mutex);

		take_forks(philosopher);

		pthread_mutex_lock(&philosopher->state_mutex);
		philosopher->state = EATING;
		pthread_mutex_unlock(&philosopher->state_mutex);

		pthread_mutex_lock(&philosopher->last_meal_mutex);
		philosopher->last_meal_time = timer();
		pthread_mutex_unlock(&philosopher->last_meal_mutex);

		printf("[ %lld ms ]%s	%s is eating%s\n", timer(), COLOR_YELLOW, philosopher->name, COLOR_RESET);
		usleep(philosopher->times->time_to_eat * 1000);
		pthread_mutex_unlock(&philosopher->fork->mutex);
		pthread_mutex_unlock(&philosopher->previous->fork->mutex);

		printf("[ %lld ms ]%s	%s is done eating!%s\n", timer(), COLOR_YELLOW, philosopher->name, COLOR_RESET);
		
		pthread_mutex_lock(&philosopher->state_mutex);
		philosopher->state = SLEEPING;
		pthread_mutex_unlock(&philosopher->state_mutex);

		printf("[ %lld ms ]%s	%s is sleeping%s\n", timer(), COLOR_BLUE, philosopher->name, COLOR_RESET);
		usleep(philosopher->times->time_to_sleep * 1000);
		printf("[ %lld ms ]%s	%s is done sleeping!%s\n", timer(), COLOR_BLUE, philosopher->name, COLOR_RESET);

		pthread_mutex_lock(&philosopher->state_mutex);
		philosopher->state = THINKING;
		pthread_mutex_unlock(&philosopher->state_mutex);
		
		printf("[ %lld ms ]%s	%s is thinking%s\n", timer(), COLOR_RESET, philosopher->name, COLOR_RESET);
		i++;
	}
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->finished = true;
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	return (NULL);
}
