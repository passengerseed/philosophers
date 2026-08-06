/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 16:49:18 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/06 19:05:14 by lrouchon         ###   ########.fr       */
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

int	rand(void)
{
	static int	rand_state;

	if (!rand_state)
		rand_state = 1;
    rand_state = (rand_state * 1103515245 + 12345) & 0x7fffffff;
    return (rand_state);
}


char	*generate_name(int	rand)
{
	char	*new_name;
	char	*tmp_name;
	char	*syl_1[10] = {"Fe", "Pou", "Bla", "To", "Pi", "Tra", "Ti", "Gi", "Ple", "Pa"};
	char	*syl_2[10] = {"plu", "tre", "flo", "cha", "dro", "que", "lle", "po", "clo", "ter"};
	char	*syl_3[10] = {"velle", "chil", "tard", "tosi", "fant", "tte", "miche", "sse", "nille", "asse"};
	int		tmp1;
	int		tmp2;
	int		tmp3;

	tmp1 = abs(rand / 1000 % 10);
	tmp2 = abs(rand / 10000 % 10);
	tmp3 = abs(rand / 100000 % 10);
	new_name = ft_strjoin(syl_1[tmp1], syl_2[tmp2]);
	tmp_name = ft_strdup(new_name);
	free(new_name);
	new_name = ft_strjoin(tmp_name, syl_3[tmp3]);
	free(tmp_name);
	return (new_name);
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
	pthread_mutex_init(&new_fork->mutex, NULL);
	new_philosopher->thread = 0;
	new_philosopher->name = name;
	new_philosopher->times = times;
	new_philosopher->fork = new_fork;
	new_philosopher->state = THINKING;
	new_philosopher->next = NULL;
	new_philosopher->previous = NULL;
	return (new_philosopher);
}

t_philosopher	*init_table(const char **argv, t_times *times)
{
	t_philosopher	*new_table;
	t_philosopher	*last;
	int				i;
	int				count;
	int				r;

	r = 0;
	new_table = NULL;
	count = ft_atoi(argv[1]);
	i = -1;
	while (++i < count)
	{
		r = rand();
		table_add_back(&new_table, init_philosopher(generate_name(r), times));
	}
	if (!new_table)
		return (NULL);
	last = table_last(new_table);
	last->next = new_table;
	new_table->previous = last;
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
