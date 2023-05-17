/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vr.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:11:19 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/17 11:09:31 by rrupp            ###   ########.fr       */
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
# include <signal.h>
# include <limits.h>

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
	bool			indic;
	bool			sorty;
	bool			hidy;
	struct s_envlst	*next;
}	t_envlst;

typedef struct s_cmdline
{
	long		nbr;
	char		*in_file;
	char		*out_file;
	char		**cmd;
	t_envlst	*enviroment;
	char		**env;
	int			fd_out;
	int			fd_in;
	pid_t		*pids;
	int			**pipe_fds;
	int			curr_err;
}	t_cmdline;

extern int	g_error;

/* signals */
int			ft_switch_signals(int sig_case);

/* env */
int			ft_parse_env(char **envp, t_envlst **env);
int			ft_lvl_up(t_envlst **lst);
int			ft_add_shlvl(t_envlst **env);
int			ft_change_lvl(char **line);
int			lst_to_ptr(t_envlst *env, char ***env_ptr);

/* lsts*/
t_envlst	*ft_lstnew_minishell(char *evar, char *cont, bool indic);
void		ft_lstadd_back_minishell(t_envlst **lst, t_envlst *new);
void		ft_lstadd_front_minishell(t_envlst **lst, t_envlst *new);
int			ft_lstsize_minishell(t_envlst *lst);

/* input_parse */
t_cmdline	**input_parse(t_envlst *env);
char		*ft_get_prompt(void);
int			ft_get_cmd(char *input, int *i, t_cmdline **todo, int *k);
int			ft_get_quotes(char *input, int *i, t_cmdline **todo, int *k);
int			ft_count_token(char *input);
char		*ft_get_token(char **input, int check);
int			ft_check_syntax(char *input);
int			ft_look_for_env(char **str, t_envlst *enviroment);
int			ft_check_open_pipe(char **input);
char		*ft_search_return_env(char *env_name, t_envlst *enviroment);
int			ft_get_parse_len(char *input, int j);
void		ft_get_parse_str(char *input, char *dest, int *i);

/* files */
int			ft_get_file(char *input, int *i, t_cmdline **todo, int nbr);
int			ft_get_outfile(char *input, int *i, t_cmdline **todo);
int			ft_get_infile(char *input, int *i, t_cmdline **todo, int nbr);

/* heredoc */
int			ft_heredoc(char *input, int *i, t_cmdline **todo, int nbr);
int			ft_fillit(t_cmdline **todo, char *doc_file);
char		*ft_getdel(char *input, int *i);
char		*ft_get_docfile(int nbr);
int			ft_fillfile(char *doc_file, char *del);

/* execution */
int			ft_execution(t_cmdline **todo);
int			ft_prep_cmd(t_cmdline *todo);
int			ft_init_exe(t_cmdline **todo, int i);
void		ft_prep_exe(t_cmdline *todo, int fd_in, int fd_out);

/* built ins */
void		ft_built_in_select(t_cmdline **todo, int i, t_envlst *env);
int			ft_built_in_check(t_cmdline **todo, int i);
int			ft_echo(t_cmdline *todo);
int			ft_cd(t_cmdline *todo, t_envlst *env);
int			ft_pwd(int fd);
int			ft_export(t_cmdline *todo, t_envlst *env);
int			ft_search_and_replace(char *todocmd, t_envlst *env);
int			ft_export_arg_execute(char *str1, char *str2, t_envlst **temp);
int			ft_valid_export_cmd(char *cmd);
int			ft_unset(t_cmdline *todo, t_envlst *env);
int			ft_env(t_envlst *env, t_cmdline *todo);
int			ft_exit(t_cmdline **todo, t_envlst *env, int i);

/* utils */
char		*ft_doublejoin(char *str1, char *str2, char *str3);
char		*ft_strncopy(char *str, unsigned int i);
long		ft_atoi_long(const char *nptr, int *j);
int			ft_search_char(char *str, char c);
int			ft_get_pwd(char **pwd);

/* free */
void		*ft_free_all(t_cmdline **todo, t_envlst *env, char **array);
void		ft_free_close(t_cmdline *todo, char *err1, char *err2);
int			ft_free_lvl_fail(t_envlst **lst, t_envlst **env);
int			ft_free_threestr(char *str1, char *str2, char *str3);
void		ft_free_exe(pid_t *pids, int **pipe_fds, int i);
#endif
