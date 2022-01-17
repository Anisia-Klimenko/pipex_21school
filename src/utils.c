/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anisiaklimenko <anisiaklimenko@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:07:45 by anisiaklime       #+#    #+#             */
/*   Updated: 2022/01/13 16:43:33 by anisiaklime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*find_cmd(char **paths, char **cmd_flags)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = NULL;
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], cmd_flags[0]);
		if (!access(cmd, F_OK))
			break ;
		free(cmd);
		i++;
	}
	if (!cmd)
		warning(errno, cmd_flags[0]);
	return (cmd);
}

char	**get_paths(char **envp)
{
	char	**paths;
	char	*tmp;
	int		i;

	i = 0;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
		{
			paths = ft_split(*envp + 5, ':');
			while (paths[i])
			{
				tmp = ft_strjoin(paths[i], "/");
				free(paths[i]);
				paths[i] = ft_strdup(tmp);
				free(tmp);
				i++;
			}
			return (paths);
		}
		envp++;
	}
	return (0);
}

void	free2(char **mas)
{
	int	i;

	i = 0;
	while (mas[i])
	{
		free(mas[i]);
		i++;
	}
	free(mas);
}

void	warning(int code, char *mess)
{
	if (code == -1)
	{
		write(2, mess, ft_strlen(mess));
		write(2, ": command not found\n", 20);
		exit(1);
	}
	perror(mess);
	exit(code);
}
