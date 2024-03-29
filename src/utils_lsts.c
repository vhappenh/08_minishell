/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lsts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 11:57:07 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/11 17:21:49 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

t_envlst	*ft_lstnew_minishell(char *evar, char *cont, bool indic)
{
	t_envlst	*ptr;

	if (evar == NULL || cont == NULL)
	{
		if (evar)
			free (evar);
		if (cont)
			free (cont);
		return (NULL);
	}
	ptr = malloc(sizeof(t_envlst));
	if (ptr == NULL)
		return (NULL);
	ptr->evar = evar;
	ptr->cont = cont;
	ptr->indic = indic;
	ptr->sorty = false;
	ptr->hidy = false;
	ptr->next = NULL;
	return ((t_envlst *)ptr);
}

void	ft_lstadd_back_minishell(t_envlst **lst, t_envlst *new)
{
	t_envlst	*ptr;

	ptr = *lst;
	if (*lst == NULL)
		return (ft_lstadd_front_minishell(lst, new));
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}

void	ft_lstadd_front_minishell(t_envlst **lst, t_envlst *new)
{
	new->next = *lst;
	*lst = new;
}

int	ft_lstsize_minishell(t_envlst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	lst_to_ptr(t_envlst *env, char ***env_ptr)
{
	int	i;

	i = ft_lstsize_minishell(env);
	*env_ptr = ft_calloc(sizeof(char **), i + 1);
	if (*env_ptr == NULL)
		return (-1);
	i = 0;
	while (env)
	{
		if (!env->indic && !env->hidy)
		{
			(*env_ptr)[i] = ft_doublejoin(env->evar, "=", env->cont);
			if ((*env_ptr)[i] == NULL)
			{
				i = 0;
				while ((*env_ptr)[i])
					free ((*env_ptr)[i]);
				free (*env_ptr);
				return (-1);
			}
			i++;
		}
		env = env->next;
	}
	return (0);
}
