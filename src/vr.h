/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:11:19 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/01 14:13:34 by vhappenh         ###   ########.fr       */
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
	char	**env;
}	t_cmdline;

typedef struct s_envlst
{
	char			*line;
	struct s_envlst	*next;
}	t_envlst;

/* main */
int			get_env(char **envp, t_envlst **env);
t_cmdline	**input_parse(void);
int			execute(t_cmdline **todo, t_envlst*env);
t_cmdline	**ft_free_array(t_cmdline **todo);

/* get_env */
t_envlst	*ft_lstnew_minishell(char *content);
void		ft_lstadd_back_minishell(t_envlst **lst, t_envlst *new);
void		ft_lstadd_front_minishell(t_envlst **lst, t_envlst *new);

/* input_parse */
char		*ft_get_prompt(void);
int			ft_djoin_spec(char *split_path, char **paths, t_cmdline *todo);
int			ft_getcmd(char *input, int *i, t_cmdline **todo, int *k);
int			ft_get_quots(char *input, int *i, t_cmdline **todo, int *k);
int			ft_get_file(char *input, int *i, t_cmdline **todo);
int			ft_get_outfile(char *input, int *i, t_cmdline **todo, int j);
int			ft_get_infile(char *input, int *i, t_cmdline **todo, int j);
int			ft_count_token(char *input);
int			ft_built_in_check(t_cmdline *todo, t_envlst *env, int fd);
char		*ft_get_token(char **input, int check);
int			ft_get_last_cmd(char **input, int i);
char		*ft_doublejoin(char *str1, char *str2, char *str3);
int			get_pwd(char **pwd);
char		*get_env_path(t_envlst *env, char *pathname);
int			ft_env(t_envlst *env, int fd);
int			lst_to_ptr(t_envlst *env, char ***env_ptr);
int			ft_lstsize_minishell(t_envlst *lst);

#endif
