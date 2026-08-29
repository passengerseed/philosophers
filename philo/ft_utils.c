/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/29 16:55:23 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/29 17:07:52 by lrouchon         ###   ########.fr       */
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

size_t	ft_count(int n)
{
	size_t	n_size;

	n_size = 1;
	if (n < 0)
	{
		n *= -1;
		n_size++;
	}
	while (n >= 10)
	{
		n /= 10;
		n_size++;
	}
	return (n_size);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*newstr;

	i = 0;
	newstr = malloc((sizeof(char) * ft_strlen(s)) + 1);
	if (!newstr)
		return (0);
	while (s[i])
	{
		newstr[i] = s[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_itoa(int n)
{
	size_t	newstr_size;
	char	*newstr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	newstr_size = ft_count(n);
	newstr = malloc(sizeof(char) * (newstr_size + 1));
	if (!newstr)
		return (0);
	newstr[newstr_size] = '\0';
	newstr_size--;
	if (n < 0)
	{
		n *= -1;
		newstr[0] = '-';
	}
	while (n > 0)
	{
		newstr[newstr_size] = (n % 10) + '0';
		n /= 10;
		newstr_size--;
	}
	return (newstr);
}

