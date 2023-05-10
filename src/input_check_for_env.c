/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_for_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:32:10 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/10 10:54:41 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static char	*ft_get_env_name(char **str, int i)
{
	int		j;
	char	*env_name;

	j = i;
	if ((*str)[j] && !ft_isalpha((*str)[j]) && (*str)[j] != '_' && (*str)[j] != '?')
		return (NULL);
	if ((*str)[j] == '?')
	{
		env_name = ft_strdup("?");
		if (env_name == NULL)
			return (NULL);
		return (env_name);
	}
	while ((*str)[j] && (ft_isalnum((*str)[j]) || (*str)[j] == '_'))
		j++;
	env_name = ft_strncopy(&(*str)[i], j - i);
	if (env_name == NULL)
		return (NULL);
	return (env_name);
}

static char *ft_rejoin_input(char **str, int i, int j, char *env)
{
	char	*tmp;
	char	*result;

	if (i > 0)
	{
		if ((*str)[i - 1] == '$')
		tmp = ft_strncopy((*str), i - 1);
		else
		tmp = ft_strncopy((*str), i);
	}
	else
		tmp = ft_strdup("");
	if (tmp == NULL)
	{
		ft_free_threestr(env, (*str), NULL);
		return (NULL);
	}
	result = ft_doublejoin(tmp, env, &(*str)[j]);
	ft_free_threestr(tmp, env, (*str));
	if (result == NULL)
		return (NULL);
	return (result);
}

static int	ft_get_env(char **str, int i, t_envlst *enviroment)
{
	char	*env;
	char	*env_name;

	env_name = ft_get_env_name(str, i);
	if (env_name == NULL)
		return (ft_free_threestr(NULL, NULL, (*str)));
	env = ft_search_return_env(env_name, enviroment);
	if (env == NULL)
		return (1);
	(*str) = ft_rejoin_input(str, i, i + ft_strlen(env_name), env);
	free(env_name);
	if ((*str) == NULL)
		return (1);
	return (0);
}

static int	ft_env_double_quotes(char **str, t_envlst *enviroment, int *i)
{
	(*i)++;
	while ((*str)[(*i)] && (*str)[(*i)] != '"')
	{
		if ((*str)[(*i)] == '$')
			if (ft_get_env(str, (*i) + 1, enviroment))
				return (1);
		if ((*str)[(*i)] != '\0')
			(*i)++;
	}
	return (0);
}

int	ft_look_for_env(char **str, t_envlst *enviroment)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] && (*str)[i] != '\'')
				i++;
		}
		if ((*str)[i] == '"')
			if (ft_env_double_quotes(str, enviroment, &i))
				return (1);
		if ((*str)[i] == '$')
		{
			if (ft_get_env(str, i + 1, enviroment))
				return (1);
		}
		if ((*str)[i] != '\0')
			i++;
	}
	return (0);
}
