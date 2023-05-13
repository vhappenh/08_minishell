/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_universal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:51:40 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/12 13:08:01 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

char	*ft_strncopy(char *str, unsigned int i)
{
	unsigned int	j;
	char			*cpy;

	j = -1;
	if (str == NULL || i < 0)
		return (NULL);
	cpy = ft_calloc(i + 1, sizeof(char));
	if (cpy == NULL)
		return (NULL);
	while (str[++j] && j < i)
		cpy[j] = str[j];
	return (cpy);
}

char	*ft_doublejoin(char *str1, char *str2, char *str3)
{
	char	*temp;
	char	*fin;

	if (!str1 || !str2 || !str3)
		return (NULL);
	temp = ft_strjoin(str1, str2);
	if (temp == NULL)
		return (NULL);
	fin = ft_strjoin(temp, str3);
	if (fin == NULL)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (fin);
}

int	ft_search_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c && str[i] != '\0')
		return (i);
	else
		return (0);
}
