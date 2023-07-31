/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functionsHelpers4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 01:10:44 by obelaizi          #+#    #+#             */
/*   Updated: 2023/07/31 01:43:35 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_cmd_helper(char *cmd, char *tmp2, char *msg)
{
	int			i;
	char		*tmp;

	i = 0;
	tmp = 0;
	if (!ft_strcmp(cmd, "."))
		return (printf("minishell: .: filename argument required\n.:\
usage: . filename [arguments]\n"), exit(2), NULL);
	else if (!ft_strcmp(cmd, ".."))
		return (printf("Minishell: %s%s", cmd, msg), exit(127), NULL);
	if (!cmd[0])
		return (printf("Minishell: %s%s", cmd, msg), exit(127), NULL);
	cmd = ft_strjoin("/", tmp2);
	while (g_data.path && g_data.path[i])
	{
		tmp = ft_strjoin(g_data.path[i], cmd);
		if (!access(tmp, F_OK))
			return (cmd = tmp, cmd);
		i++;
	}
	return (NULL);
}

char	*path_cmd(char *cmd, char *msg)
{
	struct stat	statbuf;
	char		*tmp2;

	if (count_str(cmd, "/") > 0)
		return (cmd);
	tmp2 = path_cmd_helper(cmd, cmd, msg);
	if (tmp2)
		return (tmp2);
	tmp2 = cmd;
	if (stat(tmp2, &statbuf) == 0)
	{
		if (S_ISREG(statbuf.st_mode))
		{
			if (access(tmp2, X_OK) == 0)
				return (tmp2);
		}
		else if (S_ISDIR(statbuf.st_mode))
			return (printf("minishell : %s: is a directory\n", tmp2),
				garbg_clear(&g_data.garbage), exit(126), NULL);
	}
	else
		if (errno == EACCES)
			return (printf("minishell: %s: Permission denied\n", tmp2),
				garbg_clear(&g_data.garbage), exit(126), NULL);
	return (printf("Minishell: %s%s", tmp2, msg), exit(127), NULL);
}

void	which_fd(t_pars *parsed)
{
	if (parsed->in != FD_INIT)
		dup2(parsed->in, 0);
	if (parsed->out != FD_INIT)
		dup2(parsed->out, 1);
}

void	ft_print(const char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

void	close_fds(void)
{
	t_pars	*parsed;

	parsed = g_data.pars;
	while (parsed)
	{
		if (parsed->in != FD_INIT)
			close(parsed->in);
		if (parsed->out != FD_INIT)
			close(parsed->out);
		parsed = parsed->next;
	}
}