/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:11:19 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/23 16:59:02 by rrupp            ###   ########.fr       */
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
	char	*in_file;
	char	*out_file;
	char	**cmd;
	char	*nxt_op;
}	t_cmdline;

t_cmdline	**input_parse(void);
int			execute(t_cmdline **todo, char **envp);
int			ft_free(t_cmdline **todo);
int			ft_doublejoin(char *split_path, char **paths, t_cmdline **todo);
char		*ft_get_prompt(void);
void		ft_getcmd(char *input, int *i, t_cmdline **todo, int *k);
void		ft_get_quots(char *input, int *i, t_cmdline **todo, int *k);
void		ft_get_file(char *input, int *i, t_cmdline **todo);

#endif
