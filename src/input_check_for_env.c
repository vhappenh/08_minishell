/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_for_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 11:32:10 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/24 13:38:45 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static char	*ft_get_env_name(char **str, int i)
{
	int		j;
	char	*env_name;

	j = i;
	if ((*str)[j] == '\0' || (!ft_isalpha((*str)[j]) &&
		(*str)[j] != '_' && (*str)[j] != '?' && (*str)[j] != '~'))
		return (NULL);
	if ((*str)[j] == '?' || (*str)[j] == '~')
	{
		env_name = ft_strncopy(&(*str)[j], 1);
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

static void	ft_rejoin_input(char **str, int i, int j, char *env)
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
		(*str) = (NULL);
		return ;
	}
	result = ft_doublejoin(tmp, env, &(*str)[j]);
	ft_free_threestr(tmp, env, (*str));
	(*str) = result;
	if (result == NULL)
		return ;
}

static int	ft_get_env(char **str, int i, t_envlst *enviroment)
{
	char	*env;
	char	*env_name;
	int		len;

	env_name = ft_get_env_name(str, i);
	if (env_name == NULL)
	{
		env = ft_strdup("$");
		len = 0;
	}
	else
	{
		len = ft_strlen(env_name);
		env = ft_search_return_env(env_name, enviroment);
	}
	if (env == NULL)
		return (1);
	ft_rejoin_input(str, i, i + len, env);
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

int	ft_look_for_env(char **str, t_envlst *enviroment, int i)
{
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
			if (ft_get_env(str, i + 1, enviroment))
				return (1);
		if ((*str)[i] == '~')
			if (ft_get_env(str, i, enviroment))
				return (1);
		if ((*str)[i] != '\0' && (*str)[i] != '$')
			i++;
		else if ((*str)[i] == '$' && ((*str)[i + 1] == '\0'
			|| (*str)[i + 1] == ' '))
			i++;
	}
	return (0);
}
