/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:32:10 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/04 09:56:39 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

char	*ft_search_return_env(char *env, t_envlst *enviroment)
{
	char	*tmp;

	if (env == NULL)
		return (NULL);
	tmp = NULL;
	if (!ft_strncmp(env, "?", ft_strlen(env)))
	{
		tmp = ft_itoa(errno);
		if (tmp == NULL)
			return (NULL);
		return (tmp);
	}
	while (enviroment)
	{
		if (!ft_strncmp(env, enviroment->evar, ft_strlen(env)))
		{
			tmp = ft_strdup(enviroment->cont);
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

	while ((*str)[j] && (*str)[j] != ' ' && \
		(*str)[j] != '"' && (*str)[j] != '\'')
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
		return (ft_free_threestr(env, NULL, NULL));
	result = ft_doublejoin(tmp, env, &(*str)[j]);
	if (result == NULL)
		return (ft_free_threestr(env, tmp, NULL));
	ft_free_threestr(tmp, env, (*str));
	(*str) = result;
	return (0);
}

static int	ft_env_double_quotes(char **str, t_envlst *enviroment, int *i)
{
	int	j;

	(*i)++;
	while ((*str)[(*i)] && (*str)[(*i)] != '"')
	{
		if ((*str)[(*i)] == '$')
		{
			j = (*i);
			if (ft_get_env(str, (*i), j, enviroment))
				return (1);
		}
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
			if (ft_get_env(str, i, i, enviroment))
				return (1);
		}
		if ((*str)[i] != '\0')
			i++;
	}
	return (0);
}
//there is no real check if the search return 
//fails or not it returns eater way NULL <---- Problem!!!!!