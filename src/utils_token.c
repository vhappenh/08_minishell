/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:42:16 by rrupp             #+#    #+#             */
/*   Updated: 2023/03/28 11:51:16 by rrupp            ###   ########.fr       */
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

char	*ft_get_token(char *input, int check)
{
	static int	i;
	int			j;
	int			k;
	char		c;
	char		*token;

	if (check == 0)
		i = 0;
	j = i;
	k = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			c = input[i++];
			while (input[i] || input[i] != c)
				i++;
		}
		if (input[i] == '|')
			break ;
		i++;
	}
	token = ft_calloc(i - j + 1, sizeof(char));
	while (j < i)
		token[k++] = input[j++];
	//if (token[i] == '|')
	i++;
	return (token);
}
