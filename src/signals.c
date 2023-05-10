/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:58:05 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/10 18:07:07 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

void	ft_handle_inter(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_error = 130;
	}
}

void	ft_handle_exe(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		g_error = 130;
	}
}

int	ft_switch_signals(int sig_case)
{
	if (sig_case == INTERACTIV)
	{
		signal(SIGINT, &ft_handle_inter);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_case == EXECUTING)
	{
		signal(SIGINT, &ft_handle_exe);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_case == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	return (0);
}
