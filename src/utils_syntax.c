/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:02:37 by rrupp             #+#    #+#             */
/*   Updated: 2023/04/17 11:48:27 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_print_syntax(char *input, int i)
{
	if (input[i] == '\0')
	{
		ft_putstr_fd
			("minishell: syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putchar_fd(input[i], 2);
		ft_putendl_fd("'", 2);
		return (1);
	}
}

static int	ft_checkbefor(char *input, int i)
{
//	int	check;
	int	j;

//	check = 0;
	if (i > 0 && input[i - 1] == input[i]
		&& (input[i] == '<' || input[i] == '>'))
		i--;
	j = i;
	if (j > 0)
		j--;
	while (j >= 0 && input[j] == ' ')
		j--;
	if ((input[j] == '<' || input[j] == '>') && &input[j] != &input[i])
		return (ft_print_syntax(input, i));
	if (input[i] == '|' && j == 0
		&& (input[j] == ' ' || &input[i] == &input[j]))
		return (ft_print_syntax(input, i));
	return (0);
}

int	ft_check_syntax(char *input)
{
	int	i;

	i = 0;
	while (1)
	{
		if (input[i] == '|' || input[i] == '<'
			|| input[i] == '>' || input[i] == '\0')
			if (ft_checkbefor(input, i))
				return (1);
		if (input[i])
			i++;
		else
			break ;
	}
	return (0);
}
