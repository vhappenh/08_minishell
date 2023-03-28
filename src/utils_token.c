/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:42:16 by rrupp             #+#    #+#             */
/*   Updated: 2023/03/28 09:46:13 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_count_token(char *input)
{
	int	i;
	int	tokens;

	i = 0;
	tokens = 1;
	while (input[i])
		if (input[i++] == '|')
			tokens++;
	return (tokens);
}
