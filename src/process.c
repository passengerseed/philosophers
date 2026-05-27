/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:04:58 by lrouchon          #+#    #+#             */
/*   Updated: 2026/05/27 19:34:35 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	switch_states(t_philosopher *philosopher, State new_state, int timestamp)
{
	if (new_state == EATING && philosopher->fork != NULL)
		printf("%d	%s %s\n", timestamp, philosopher->name, "is eating");
	else if (new_state == EATING && philosopher->fork != NULL)
		return (printf("%d	%s %s\n", timestamp, philosopher->name, "tried to eat, but has no fork!"), -1);
	else if (new_state == SLEEPING)
		printf("%d	%s %s\n", timestamp, philosopher->name, "is sleeping");
	else if (new_state == THINKING)
		printf("%d	%s %s\n", timestamp, philosopher->name, "is thinking");
	else if (new_state == DEAD)
		printf("%d	%s %s\n", timestamp, philosopher->name, "died");
	else
		return(error("couldn't change state"), -1);
	philosopher->state = new_state;
	return (0);
}

int	eat(t_philosopher *philosopher)
{
	int				status;
	__useconds_t	time;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	pthread_mutex_t	*tmp;

	time = philosopher->times->time_to_eat;
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
	pthread_mutex_lock(second);
	status = usleep(time);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
	printf("%s is done eating!\n", philosopher->name);
	return (status);
}

void	*live(void *arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	printf("> created a thread for: %s\n", philosopher->name);
	return (NULL);
}
