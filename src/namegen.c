/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   namegen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:16:03 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/14 18:26:10 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

char	*ft_strjoin(
	const char	*s1,
	const char	*s2
)
{
	size_t	i;
	size_t	j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = malloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2))) + 1);
	if (!newstr)
		return (0);
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}

char	*generate_name(int rand)
{
	char		*new_name;
	char		*tmp_name;
	const char	*syl_1[10] = {"Fe", "Pou", "Bla", "To", "Pi", "Tra", "Ti", "Gi", "Ple", "Pa"};
	const char	*syl_2[10] = {"plu", "tre", "flo", "cha", "dro", "que", "lle", "po", "clo", "ter"};
	const char	*syl_3[10] = {"velle", "chil", "tard", "tosi", "fant", "tte", "miche", "sse", "nille", "asse"};
	int			tmp[3];

	tmp[0] = abs(rand / 1000 % 10);
	tmp[1] = abs(rand / 10000 % 10);
	tmp[2] = abs(rand / 100000 % 10);
	new_name = ft_strjoin(syl_1[tmp[0]], syl_2[tmp[1]]);
	tmp_name = ft_strdup(new_name);
	free(new_name);
	new_name = ft_strjoin(tmp_name, syl_3[tmp[2]]);
	free(tmp_name);
	return (new_name);
}
