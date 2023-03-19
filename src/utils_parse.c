/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 09:39:30 by rrupp             #+#    #+#             */
/*   Updated: 2023/03/19 13:22:11 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vr.h"

char *ft_free_prompt(char *wd, char *user, char *manager)
{
	if (wd)
		free(wd);
	if (user)
		free(user);
	if (manager)
		free(manager);
	perror("zsh");
	return (NULL);
}

char	*ft_get_prompt(char **envp)
{
	char	*wd;
	char	*user;
	char	*temp;
	//char	manager[100];
	//char	*prompt;
	(void) envp;
	wd = ft_calloc(1024, sizeof(char));
	if (wd == NULL)
		return (ft_free_prompt(NULL, NULL, NULL));
	wd = getcwd(wd, 1024);
	user = getenv("USER");
	if (user == NULL)
		return (ft_free_prompt(wd, NULL, NULL));
	temp = wd;
	while (wd && ft_strncmp(wd, user, ft_strlen(user)))
		wd++;
	wd += ft_strlen(user);
	printf("%s\n", wd);
	return (wd);
}