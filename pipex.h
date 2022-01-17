/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anisiaklimenko <anisiaklimenko@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:06:42 by anisiaklime       #+#    #+#             */
/*   Updated: 2022/01/13 15:28:19 by anisiaklime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

char	**get_paths(char **envp);
char	*find_cmd(char **paths, char **cmd_flags);

void	warning(int code, char *mess);
void	free2(char **mas);

#endif