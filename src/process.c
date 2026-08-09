/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:04:58 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/09 20:43:40 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	switch_states(
	t_philosopher *philosopher,
	State new_state,
	long long timestamp
)
{
	if (new_state == EATING && philosopher->fork != NULL)
	{
		eat(philosopher, timestamp);
	}
	else if (new_state == EATING && (philosopher->fork == NULL || philosopher->previous->fork == NULL))
	{
		printf("%lld	%s %s\n", timestamp, philosopher->name, "tried to eat, but has no fork!");
		return (-1);
	}
	else if (new_state == SLEEPING)
	{
		philosopher->state = new_state;
		nap(philosopher, timestamp);
	}
	else if (new_state == THINKING)
	{
		philosopher->state = new_state;
		printf("%lld	%s %s\n", timer(), philosopher->name, "is thinking");
	}
	else if (new_state == DEAD)
	{
		philosopher->state = new_state;
		die(philosopher, timestamp);
	}
	else
		return (error("couldn't change state"), -1);
	return (0);
}

int	eat(
	t_philosopher *philosopher,
	long long timestamp
)
{
	int				status;
	__useconds_t	time;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	pthread_mutex_t	*tmp;

	(void)timestamp;
	time = philosopher->times->time_to_eat * 1000;
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
	printf("%lld	%s has taken a fork\n", timer(), philosopher->name);
	pthread_mutex_lock(second);
	printf("%lld	%s has taken a fork\n", timer(), philosopher->name);
	philosopher->state = EATING;
	printf("%lld	%s is eating\n", timer(), philosopher->name);
	status = usleep(time);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->last_meal_time = timer();
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	printf("%lld	%s is done eating!\n", timer(), philosopher->name);
	return (status);
}

int	nap(
	t_philosopher *philosopher,
	long long timestamp
)
{
	int				status;
	__useconds_t	time;

	(void)timestamp;
	time = philosopher->times->time_to_sleep * 1000;
	printf("%lld	%s is sleeping\n", timer(), philosopher->name);
	status = usleep(time);
	printf("%lld	%s is done sleeping!\n", timer(), philosopher->name);
	return (status);
}

void	die(
	t_philosopher *philosopher,
	long long timestamp
)
{
	printf("%lld	%s died!\n", timestamp, philosopher->name);
	exit(EXIT_SUCCESS);
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
		if (philosopher->state == THINKING)
			switch_states(philosopher, EATING, timer());
		if (philosopher->state == EATING)
		{
			i++;
			switch_states(philosopher, SLEEPING, timer());
		}
		if (philosopher->state == SLEEPING)
			switch_states(philosopher, THINKING, timer());
	}
	pthread_mutex_lock(&philosopher->last_meal_mutex);
	philosopher->finished = true;
	pthread_mutex_unlock(&philosopher->last_meal_mutex);
	return (NULL);
}
