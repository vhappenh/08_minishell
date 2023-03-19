/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:26:29 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/19 09:51:39 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

char	*input_parse(t_cmdline **todo, char **envp)
{
	char				*prompt;
	char				*input;

	prompt = ft_get_prompt(envp);
	input = readline(prompt);
	if (ft_strlen(input) == 4 && !ft_strncmp(input, "exit", 4))
	{
		ft_printf("%s\n", input);
		free(input);
		return (NULL);
	}
	add_history(input);
	(void)todo;
	(void)input;
	return (input);
}
