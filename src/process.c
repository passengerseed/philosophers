/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:04:58 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/17 16:46:11 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


// printf("[ %lld ms ]	%s has taken a fork\n", timer(), philosopher->name);

int	take_fork(t_philosopher *philosopher)
{
	t_fork	*first;
	t_fork	*second;

	first = philosopher->fork;
	second = philosopher->previous->fork;

	pthread_mutex_lock(&first->mutex);
	printf("[ %lld ms ]	%s has taken a fork\n", timer(), philosopher->name);
	pthread_mutex_lock(&second->mutex);
	printf("[ %lld ms ]	%s has taken a fork\n", timer(), philosopher->name);
	pthread_mutex_unlock(&first->mutex);
	pthread_mutex_unlock(&second->mutex);
	return (0);
}

void	*lifecycle(void	*arg)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)arg;
	printf("[ %lld ms ]	%s has taken a fork\n", timer(), philosopher->name);
	return (0);
}

