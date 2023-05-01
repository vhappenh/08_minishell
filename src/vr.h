/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:11:19 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/01 15:09:01 by vhappenh         ###   ########.fr       */
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
# include <errno.h>

# ifndef INTERACTIV
#  define INTERACTIV 0
# endif
# ifndef EXECUTING
#  define EXECUTING 1
# endif
# ifndef CHILD
#  define CHILD 2
# endif

typedef struct s_envlst
{
	char			*evar;
	char			*cont;
	int				indic;
	struct s_envlst	*next;
}	t_envlst;

typedef struct s_cmdline
{
	long		nbr;
	char		*prev_op;
	char		*in_file;
	char		*out_file;
	char		**cmd;
	char		*nxt_op;
	t_envlst	*enviroment;
	t_list		*exportvar;
	char		**env;
	int			fd_out;
	int			fd_in;
	pid_t		*pids;
	int			**pipe_fds;
}	t_cmdline;

/* main */
int			get_env(char **envp, t_envlst **env);
t_cmdline	**input_parse(t_envlst *env);
int			execute(t_cmdline **todo, t_envlst*env);
void		*ft_free_all(t_cmdline **todo, t_envlst *env, char **array);

/* get_env */
t_envlst	*ft_lstnew_minishell(char *evar, char *cont, int indic);
void		ft_lstadd_back_minishell(t_envlst **lst, t_envlst *new);
void		ft_lstadd_front_minishell(t_envlst **lst, t_envlst *new);

/* input_parse */
char		*ft_get_prompt(void);
int			ft_djoin_spec(char *split_path, char **paths, t_cmdline *todo);
int			ft_getcmd(char *input, int *i, t_cmdline **todo, int *k);
int			ft_get_quots(char *input, int *i, t_cmdline **todo, int *k);
int			ft_get_file(char *input, int *i, t_cmdline **todo, int nbr);
int			ft_get_outfile(char *input, int *i, t_cmdline **todo);
int			ft_get_infile(char *input, int *i, t_cmdline **todo, int nbr);
int			ft_count_token(char *input);
int			ft_built_in_check(t_cmdline **todo, int i, t_envlst *env);
char		*ft_get_token(char **input, int check);
char		*ft_doublejoin(char *str1, char *str2, char *str3);
int			get_pwd(char **pwd);
char		*get_env_path(t_envlst *env, char *pathname);
int			ft_env(t_envlst *env, t_cmdline *todo);
int			lst_to_ptr(t_envlst *env, char ***env_ptr);
int			ft_lstsize_minishell(t_envlst *lst);
int			save_pwd(t_envlst *env, char *pwd);
int			save_old_pwd(t_envlst *env, char *pwd);
int			cd_dot_dot(char *pwd, char **new_path);
int			ft_exit(t_cmdline **todo, t_envlst *env, int i);
int			ft_unset(t_cmdline *todo, t_envlst *env);
int			ft_change_lvl(char **line);
char		*ft_strncopy(char *str, unsigned int i);
int			ft_heredoc(char *input, int *i, t_cmdline **todo, int nbr);
int			ft_lvl_up(t_envlst **lst);
int			ft_add_shlvl(t_envlst **env);
int			ft_found_target(t_envlst **temp, t_envlst **head);
int			ft_free_lvl_fail(t_envlst **lst, t_envlst **env);
int			ft_check_syntax(char *input);
int			ft_export(t_cmdline *todo, t_envlst *env);
int			ft_look_for_env(char **str, t_envlst *enviroment);
int			ft_check_open_pipe(char **input);
int			ft_search_char(char *str, char c);
int			ft_free_threestr(char *str1, char *str2, char *str3);
/*signals*/
int			ft_switch_signals(int sig_case);
int			ft_execution(t_cmdline **todo);
int			ft_prep_cmd(t_cmdline *todo);
void		ft_free_exe(pid_t *pids, int **pipe_fds, int i);
int			ft_init_exe(t_cmdline **todo, int i);
#endif
