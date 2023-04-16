/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:32:10 by rrupp             #+#    #+#             */
/*   Updated: 2023/04/16 11:24:30 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_freeenv(char *str1, char *str2, char *str3)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
	return (1);
}

char	*ft_search_return_env(char *env, t_envlst *enviroment)
{
	char	*tmp;

	if (env == NULL)
		return (NULL);
	tmp = env;
	env = ft_strjoin(tmp, "=");
	if (env == NULL)
		return (NULL);
	free(tmp);
	tmp = NULL;
	while (enviroment)
	{
		if (!ft_strncmp(env, enviroment->line, ft_strlen(env)))
		{
			tmp = ft_strncopy(enviroment->line, ft_strlen(enviroment->line));
			if (tmp == NULL)
				return (NULL);
			break ;
		}
		else
			enviroment = enviroment->next;
	}
	return (tmp);
}

char	*ft_get_env_name(char *str)
{
	char	*env;
	int		j;

	j = 0;
	str++;
	while (str[j] && str[j] != ' ')
		j++;
	env = ft_strncopy(str, j - 1);
	if (env == NULL)
		return (NULL);
	return (env);
}

static int	ft_get_env(char **str, int i, int j, t_envlst *enviroment)
{
	char	*env;
	char	*tmp;
	char	*result;

	while ((*str)[j] && (*str)[j] != ' ')
		j++;
	env = ft_strncopy((&(*str)[i] + 1), j - i - 1);
	if (env == NULL)
		return (1);
	env = ft_search_return_env(env, enviroment);
	if (env == NULL)
		env = ft_strdup("");
	if (i > 0)
		tmp = ft_strncopy((*str), i);
	else
		tmp = ft_strdup("");
	if (tmp == NULL)
		return (ft_freeenv(env, NULL, NULL));
	result = ft_doublejoin(tmp, env, &(*str)[j]);
	if (result == NULL)
		return (ft_freeenv(env, tmp, NULL));
	ft_freeenv(tmp, env, (*str));
	(*str) = result;
	return (0);
}

int	ft_look_for_env(char **str, t_envlst *enviroment)
{
	int		i;
	int		j;

	i = 0;
	while ((*str)[i])
	{
		while ((*str)[i] && ((*str)[i] != '$' || (*str)[i] != '\''))
			i++;
		j = i;
		if ((*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] && (*str)[i] != '\'')
				i++;
		}
		if ((*str)[i] == '$')
			if (ft_get_env(str, i, j, enviroment))
				return (1);
		i++;
	}
	return (0);
}
//there is no real check if the search return 
//fails or not it returns eater way NULL <---- Problem!!!!!