/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 19:05:27 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/14 19:05:29 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_table(t_philosopher *philosopher)
{
	int	i;
	int	j;

	i = -1;
	j = philosopher->times->philosopher_amount;
	printf("\n	TIME TO DIE:	%dms\n", philosopher->times->time_to_die);
	printf("	TIME TO EAT:	%dms\n", philosopher->times->time_to_eat);
	printf("	TIME TO SLEEP:	%dms\n\n", philosopher->times->time_to_sleep);
	printf("--- TABLE: ----------------------------\n");
	while (++i < j)
	{
		printf("> %s	%lu\n", philosopher->name, philosopher->thread);
		philosopher = philosopher->next;
	}
	printf("---------------------------------------\n");
	printf("DINNER TIME! :)\n\n");
}
