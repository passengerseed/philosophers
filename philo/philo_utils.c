/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 16:55:25 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/29 19:59:00 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	timer(void)
{
	static long long	start_time_ms;
	struct timeval		tv;

	if (!start_time_ms)
	{
		gettimeofday(&tv, NULL);
		start_time_ms = tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;
	}
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL + tv.tv_usec / 1000LL) - start_time_ms);
}

void	print_lock(t_philosopher *philosopher, char *str)
{
	pthread_mutex_lock(&philosopher->sync->print_mutex);
	if (!is_dead(philosopher))
		printf("[ %lld ms ]	%s %s\n", timer(), philosopher->name, str);
	pthread_mutex_unlock(&philosopher->sync->print_mutex);
}

void	ft_usleep(long long duration, t_philosopher *philosopher)
{
	long long	start;

	start = timer();
	while (timer() - start < duration)
	{
		if (is_dead(philosopher))
			return ;
		usleep(500);
	}
}

t_philosopher	*table_last(t_philosopher *philosopher)
{
	if (!philosopher)
		return (NULL);
	if (!philosopher->next)
		return (philosopher);
	return (table_last(philosopher->next));
}

void	table_add_back(
	t_philosopher **table,
	t_philosopher *new_philosopher
)
{
	t_philosopher	*current;

	if (!*table)
	{
		*table = new_philosopher;
		return ;
	}
	current = table_last(*table);
	current->next = new_philosopher;
	new_philosopher->next = NULL;
	new_philosopher->previous = current;
}
