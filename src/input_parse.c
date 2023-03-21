/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:26:29 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/21 13:31:54 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

char	*input_parse(t_cmdline **todo)
{
	char				*prompt;
	char				*input;

	prompt = ft_get_prompt();
	input = readline(prompt);
	if (ft_strlen(input) == 4 && !ft_strncmp(input, "exit", 4))
	{
		ft_printf("%s\n", input);
		free(input);
		free(prompt);
		return (NULL);
	}
	add_history(input);
	free(prompt);
	(void)todo;
	(void)input;
	return (input);
}
