/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:45:55 by rrupp             #+#    #+#             */
/*   Updated: 2023/03/16 14:22:23 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vr.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
	char	*input;

	while (1)
	{
		input = readline("minishell: ");
		if (ft_strlen(input) == 4 && !ft_strncmp(input, "exit", 4))
		{
			printf("%s\n", input);
			free(input);
			return (0);
		}
		add_history(input);
		printf("%s\n", input);
		free(input);
		rl_on_new_line();
	}
}
