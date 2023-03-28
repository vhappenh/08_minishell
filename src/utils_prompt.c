/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:39:30 by rrupp             #+#    #+#             */
/*   Updated: 2023/03/21 14:42:50 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

char	*ft_free_prompt(char *wd, char *manager)
{
	if (wd)
		free(wd);
	if (manager)
		free(manager);
	perror("zsh");
	return (NULL);
}

char	*ft_fillit(char *wd, char *user, char *manager, char *tmp)
{
	int		len[4];
	int		i;
	int		j;
	char	*prompt;

	len[0] = ft_strlen(wd);
	len[1] = ft_strlen(user);
	len[2] = ft_strlen(manager);
	len[3] = len[0] + len[1] + len[2] + 2;
	prompt = ft_calloc(len[3] + 1, sizeof(char));
	if (prompt == NULL)
		ft_free_prompt(tmp, manager);
	i = 0;
	j = 0;
	while (j < len[1])
		prompt[i++] = user[j++];
	j = 0;
	while (j < len[2])
		prompt[i++] = manager[j++];
	j = 0;
	while (j < len[0])
		prompt[i++] = wd[j++];
	prompt[i] = '$';
	prompt[i + 1] = ' ';
	return (prompt);
}

char	*ft_get_manager(char *manager)
{
	int		i;
	char	*tmp;

	i = 0;
	while (manager[i] != '/')
		i++;
	tmp = ft_strdup(&manager[i]);
	free(manager);
	if (tmp == NULL)
		return (NULL);
	tmp[0] = '@';
	while (tmp[i] != '.')
		i++;
	tmp[i] = ':';
	tmp[i + 1] = '\0';
	return (tmp);
}

char	*ft_cut_wd(char *user, char *wd)
{
	char	*temp;

	temp = wd;
	while (ft_strncmp(temp, user, ft_strlen(user)))
		temp++;
	temp += ft_strlen(user) - 1;
	temp[0] = '~';
	return (temp);
}

char	*ft_get_prompt(void)
{
	char	*wd;
	char	*user;
	char	*manager;
	char	*prompt;
	char	*tmp_wd;

	wd = ft_calloc(1024, sizeof(char));
	if (wd == NULL)
		return (ft_free_prompt(NULL, NULL));
	wd = getcwd(wd, 1024);
	user = getenv("USER");
	manager = ft_strdup(getenv("SESSION_MANAGER"));
	if (manager == NULL)
		return (ft_free_prompt(wd, NULL));
	manager = ft_get_manager(manager);
	tmp_wd = ft_cut_wd(user, wd);
	prompt = ft_fillit(tmp_wd, user, manager, wd);
	free(wd);
	free(manager);
	return (prompt);
}