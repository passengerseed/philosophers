/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   namegen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrouchon <lrouchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 19:16:03 by lrouchon          #+#    #+#             */
/*   Updated: 2026/08/06 19:23:20 by lrouchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	rand(void)
{
	static int	rand_state;

	if (!rand_state)
		rand_state = 1;
	rand_state = (rand_state * 1103515245 + 12345) & 0x7fffffff;
	return (rand_state);
}

char	*generate_name(int rand)
{
	char	*new_name;
	char	*tmp_name;
	char	*syl_1[10] = {"Fe", "Pou", "Bla", "To", "Pi", "Tra", "Ti", "Gi", "Ple", "Pa"};
	char	*syl_2[10] = {"plu", "tre", "flo", "cha", "dro", "que", "lle", "po", "clo", "ter"};
	char	*syl_3[10] = {"velle", "chil", "tard", "tosi", "fant", "tte", "miche", "sse", "nille", "asse"};
	int		tmp[3];

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
