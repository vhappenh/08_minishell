/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:11:19 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/21 10:50:14 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VR_H
# define VR_H
# include "libft_ultra/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

typedef struct s_cmdline
{
	char	*prev_op;
	char	*file;
	char	**cmd;
	char	*nxt_op;
}	t_cmdline;

char	*input_parse(t_cmdline **todo);
int		execute(t_cmdline **todo, char **envp);
int		ft_free(t_cmdline **todo);
int		ft_doublejoin(char *split_path, char **paths, t_cmdline **todo);
char	*ft_get_prompt(void);

#endif
