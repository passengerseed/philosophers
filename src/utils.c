/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 17:12:52 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/18 16:15:14 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static	int	ft_isspace(unsigned char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	sign;

	i = 0;
	n = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		n *= 10;
		n += (str[i] - '0');
		i++;
	}
	return (n * sign);
}

int	ft_rand(void)
{
	static int	rand_state;

	if (!rand_state)
		rand_state = 1;
	rand_state = (rand_state * 1103515245 + 12345) & 0x7fffffff;
	return (rand_state);
}

void	print_lock(t_philosopher *philosopher, char *str)
{	
	if (is_dead(philosopher))
		return ;
	pthread_mutex_lock(&philosopher->sync->print_mutex);
	printf("[ %lld ms ]	%s %s\n", timer(), philosopher->name, str);
	pthread_mutex_unlock(&philosopher->sync->print_mutex);
}
