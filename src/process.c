/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:04:58 by lrouchon          #+#    #+#             */
/*   Updated: 2026/05/27 19:23:30 by lrouchon         ###   ########.fr       */
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

	time = philosopher->times->time_to_eat;
	pthread_mutex_lock(&philosopher->fork->mutex);
	pthread_mutex_lock(&philosopher->previous->fork->mutex);
	status = usleep(time);
	pthread_mutex_unlock(&philosopher->fork->mutex);
	pthread_mutex_unlock(&philosopher->previous->fork->mutex);
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
