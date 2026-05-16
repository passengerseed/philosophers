/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 16:49:18 by lrouchon          #+#    #+#             */
/*   Updated: 2026/05/16 16:57:12 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_times	*init_times(const char **argv)
{
	t_times	*new_times;

	new_times = malloc(sizeof(t_times));
	if (!new_times)
		return (NULL);
	new_times->philosopher_amount = ft_atoi(argv[1]);
	new_times->time_to_die = ft_atoi(argv[2]);
	new_times->time_to_eat = ft_atoi(argv[3]);
	new_times->time_to_sleep = ft_atoi(argv[4]);
	return (new_times);
}

// char	*generate_name(long unsigned *thread_id)
// {
// 	char	*new_name;
// 	char	*syl_1[10] = {"Fe", "Pat", "Bla", "To", "Pi", "Tra", "Ti", "Gi", "Ple", "Pha"};
// 	char	*syl_2[10] = {"plu", "tre", "flo", "cha", "dro", "cce", "lle", "po", "clo", "ter"};
// 	char	*syl_3[10] = {"velle", "chil", "tard", "tosis", "bli", "tte", "chre", "sse", "nille", "asse"};
// 	int		tmp1;
// 	int		tmp2;
// 	int		tmp3;

// 	(void)syl_2;
// 	(void)syl_3;
// 	tmp1 = abs((*(int *)thread_id) / 1000 % 10);
// 	tmp2 = abs((*(int *)thread_id) / 10000 % 10);
// 	tmp3 = abs((*(int *)thread_id) / 100000 % 10);
// 	new_name = syl_1[tmp_1];
// 	return (new_name);
// }

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
	// new_philosopher->name = generate_name((long unsigned *)new_philosopher->thread);
	new_philosopher->name = name;
	new_philosopher->times = times;
	new_philosopher->fork_left = new_fork;
	new_philosopher->fork_right = NULL;
	new_philosopher->state = INIT;
	eat(new_philosopher);
	// pthread_join(new_philosopher->thread, NULL);
	return (new_philosopher);
}

t_philosopher	*init_table(const char **argv, t_times *times)
{
	t_philosopher	*new_table;
	t_philosopher	*head;
	int				i;

	new_table = NULL;
	i = -1;
	while (++i < ft_atoi(argv[1]))
		table_add_back(&new_table, init_philosopher("Soraya", times));
	head = new_table;
	new_table->previous = table_last(new_table);
	new_table = table_last(new_table);
	new_table->next = head;
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
