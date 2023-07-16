/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:15:43 by aait-mal          #+#    #+#             */
/*   Updated: 2023/07/16 01:56:39 by aait-mal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "Libft/libft.h"

enum e_type
{
	PIPE = 1,
	HEREDOC,
	APPEND,
	OUT,
	IN,
	FD,
	CMD,
};

enum e_quote
{
	SQ = 1,
	DQ,
};
typedef struct cmds
{
	char			*s;
	enum e_type		type;
	enum e_quote	quote;
	struct cmds		*next;
	struct cmds		*prev;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct parsing
{
	t_cmd			*cmd;
	struct parsing	*next;
	int				out;
	int				in;

}	t_pars;

typedef struct minikhell
{
	char	**path;
	char	*input;
	t_env	*env;
	t_cmd	*cmds;
	t_pars	*pars;
	char	**builtins;
}	t_data;

t_data g_data;

t_env	*env_new(char *key, char *value);
void	env_add_back(t_env **lst, t_env *new);
void	env_delone(t_env *lst);
int		env_size(t_env *lst);
void	env_clear(t_env **lst);

t_cmd	*cmd_new(char *s);
void	cmd_add_back(t_cmd **lst, t_cmd *new);
void	cmd_front(t_cmd **lst, t_cmd *new);
int		cmd_size(t_cmd *lst);
void	cmd_clear(t_cmd **lst);
void	make_it_prev(void);

t_pars	*parse_new(t_cmd *cmd);
void	parse_add_back(t_pars **lst, t_pars *new);
int		parse_size(t_pars *lst);
void	parse_clear(t_pars **lst);
void	parse_front(t_pars **lst, t_pars *new);

int		is_closed(const char *s);
void	display_prompt(void);
void	parse(char *str);
int		count_str(const char *s, const char *s1);
void	cust_split(char *s);
void	upgrade_splt(const char *sep);
char	*get_name_var(char *argument);
char	*get_val_var(char *argument);
int		is_syntax_error(void);

void	echo(char *str, int flag);
void	cd(char *path);
void	pwd(void);
void	export(char *argument);
void	unset(char *s);
void	env(int is_env);
void	expand(t_cmd *node);

char	*path_cmd(char *cmd);
void	set_builtins(void);
void	execute(void);

#endif
