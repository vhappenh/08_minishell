/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:58:05 by rrupp             #+#    #+#             */
/*   Updated: 2023/04/27 14:34:10 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static void	ft_handle_inter(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	ft_handle_exe(int signum)
{
	if (signum == SIGINT)
		write(1, "\n", 1);
	else if (signum == SIGQUIT)
		;
}

static int	ft_sig_interactiv(struct sigaction sa)
{
	sa.sa_handler = &ft_handle_inter;
	if (sigaction(SIGINT, &sa, NULL))
		return (1);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

static int	ft_sig_executing(struct sigaction sa)
{
	sa.sa_handler = &ft_handle_exe;
	if (sigaction(SIGINT, &sa, NULL))
		return (1);
	if (sigaction(SIGQUIT, &sa, NULL))
		return (1);
	return (0);
}

int	ft_switch_signals(int sig_case)
{
	static struct sigaction	sa;

	if (sig_case == INTERACTIV)
	{
		if (ft_sig_interactiv(sa))
			return (1);
	}
	else if (sig_case == EXECUTING)
	{
		if (ft_sig_executing(sa))
			return (1);
	}
	else if (sig_case == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	return (0);
}
