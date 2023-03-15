/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:11:19 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/15 14:35:16 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VR_H
# define VR_H
# include <stdio.h>

typedef struct s_cmdline
{
	char	*prev_op;
	char	*file;
	char	*cmd;
	char	*nxt_op;
}	t_cmdline;

int		input_parse(t_cmdline **todo);
int		execute(t_cmdline *todo, char **envp);

#endif
