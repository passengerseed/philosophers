/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 16:49:18 by lrouchon          #+#    #+#             */
/*   Updated: 2026/05/10 19:54:55 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_times	*init_times(const char **argv)
{
	t_times	*new_times;

	new_times = malloc(sizeof(t_times));
	if (!new_times)
		return (NULL);
	new_times->time_to_die = ft_atoi(argv[2]);
	new_times->time_to_eat = ft_atoi(argv[3]);
	new_times->time_to_sleep = ft_atoi(argv[4]);
	return (new_times);
}

t_philosopher	*init_philosopher(char *name, t_times *times)
{
	t_philosopher	*new_philosopher;
	t_fork			*new_fork;

	new_philosopher = malloc(sizeof(t_philosopher));
	if (!new_philosopher)
		return (NULL);
	new_fork = malloc(sizeof(t_fork));
	if (!new_fork)
		return (free(new_philosopher), NULL);
	pthread_create(&new_philosopher->thread, NULL, live, new_philosopher);
	new_philosopher->name = name;
	new_philosopher->times = times;
	new_philosopher->fork = new_fork;
	new_philosopher->state = INIT;
	pthread_join(new_philosopher->thread, NULL);
	return (new_philosopher);
}

t_philosopher	*init_table(const char **argv, t_times *times)
{
	t_philosopher	*new_table;
	int				i;

	new_table = NULL;
	i = -1;
	while (++i < ft_atoi(argv[1]))
		table_add_back(&new_table, init_philosopher("Steve", times));
	return (new_table);
}

t_philosopher	*table_last(t_philosopher *philosopher)
{
	if (!philosopher)
		return (NULL);
	if (!philosopher->next)
		return (philosopher);
	return (table_last(philosopher->next));
}


void	table_add_back(t_philosopher **table, t_philosopher *new_philosopher)
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

void	table_add_front(t_philosopher **table, t_philosopher *new_philosopher)
{
	new_philosopher->next = *table;
	if (new_philosopher->next)
		new_philosopher->next->previous = new_philosopher;
	new_philosopher->previous = NULL;
	*table = new_philosopher;
}

// void	clear_table(t_philosopher **table)
// {
// 	t_philosopher	*current;

// 	current = *table;
// 	while (current)
// 	{
// 		current = current->next;
// 		free(current->previous);
// 	}
// 	free(current);
// 	free(table);
// }
