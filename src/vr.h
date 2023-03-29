/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:11:19 by vhappenh          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/29 11:48:36 by vhappenh         ###   ########.fr       */
=======
/*   Updated: 2023/03/28 15:05:24 by rrupp            ###   ########.fr       */
>>>>>>> 78d79680a1bc493b61fe76389ed74a5f49bd53be
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
	long	nbr;
	char	*prev_op;
	char	*in_file;
	char	*out_file;
	char	**cmd;
	char	*nxt_op;
}	t_cmdline;

t_cmdline	**input_parse(void);
int			execute(t_cmdline **todo, char **envp);
int			ft_free(t_cmdline **todo);
int			ft_doublejoin(char *split_path, char **paths, t_cmdline *todo);
char		*ft_get_prompt(void);
int			ft_getcmd(char *input, int *i, t_cmdline **todo, int *k);
int			ft_get_quots(char *input, int *i, t_cmdline **todo, int *k);
int			ft_get_file(char *input, int *i, t_cmdline **todo);
int			ft_get_outfile(char *input, int *i, t_cmdline **todo, int j);
int			ft_get_infile(char *input, int *i, t_cmdline **todo, int j);
t_cmdline	**ft_free_array(t_cmdline **todo);
int			ft_count_token(char *input);
<<<<<<< HEAD
char		*ft_get_token(char *input, int check);
int			ft_built_in_check(t_cmdline *todo, int fd);
=======
char		*ft_get_token(char **input, int check);
>>>>>>> 78d79680a1bc493b61fe76389ed74a5f49bd53be

#endif
