/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:42:16 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/06 15:13:06 by vhappenh         ###   ########.fr       */
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

static int	ft_jump_quotes(char *input, int i)
{
	char	c;

	c = input[i++];
	while (input[i] && input[i] != c)
		i++;
	return (i);
}

static int	ft_get_length(char *input, int i)
{
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i = ft_jump_quotes(input, i);
		if (input[i] == '|')
			break ;
		if (input[i])
			i++;
	}
	return (i);
}

char	*ft_get_token(char **input, int check)
{
	static int	i;
	int			j;
	int			k;
	char		*token;

	if (check == 0)
		i = 0;
	while ((*input)[i] == ' ')
		i++;
	j = i;
	k = 0;
	i = ft_get_length((*input), i);
	token = ft_calloc(i - j + 1, sizeof(char));
	if (token == NULL)
		return (NULL);
	while (j < i)
		token[k++] = (*input)[j++];
	i++;
	return (token);
}