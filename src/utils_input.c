/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:54:57 by rrupp             #+#    #+#             */
/*   Updated: 2023/03/23 15:31:13 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

void	ft_getcmd(char *input, int *i, t_cmdline **todo, int k)
{
	int	j;
	int	d;

	j = (*i);
	while (input[j] && input[j] != ' ')
		j++;
	(*todo)->cmd[k] = ft_calloc(j - (*i) + 1, sizeof(char));
	d = 0;
	while ((*i) < j)
		(*todo)->cmd[k][d++] = input[(*i)++];
}