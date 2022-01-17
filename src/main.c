/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anisiaklimenko <anisiaklimenko@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:06:17 by anisiaklime       #+#    #+#             */
/*   Updated: 2022/01/13 16:47:08 by anisiaklime      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	execute(char *arg, char **envp)
{
	char	**paths;
	char	**cmd_flags;
	char	*cmd;

	paths = get_paths(envp);
	if (!paths)
		warning(errno, "PATH: ");
	cmd_flags = ft_split(arg, ' ');
	if (!cmd_flags)
	{
		free2(paths);
		warning(errno, "malloc: ");
	}
	cmd = find_cmd(paths, cmd_flags);
	if (execve(cmd, cmd_flags, NULL) == -1)
		warning(-1, cmd_flags[0]);
	free2(paths);
	free2(cmd_flags);
}

void	child_one(int *fd, char **argv, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
		warning(errno, argv[1]);
	if (dup2(fd_in, STDIN_FILENO) < 0)
		warning(errno, "Error: ");
	if (dup2(fd[1], STDOUT_FILENO) < 0)
		warning(errno, "Error: ");
	close (fd_in);
	close (fd[0]);
	close (fd[1]);
	execute(argv[2], envp);
}

void	child_two(int *fd, char **argv, char **envp)
{
	int	fd_out;

	fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out < 0)
		warning(errno, argv[4]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		warning(errno, "Error: ");
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		warning(errno, "Error: ");
	close (fd_out);
	close (fd[0]);
	close (fd[1]);
	execute(argv[3], envp);
}

void	pipex(char **argv, char **envp)
{
	pid_t	child1;
	pid_t	child2;
	int		fd[2];

	if (pipe(fd) == -1)
		warning(errno, "pipex: ");
	child1 = fork();
	if (child1 < 0)
		warning(errno, "fork: ");
	if (!child1)
		child_one(fd, argv, envp);
	child2 = fork();
	if (child2 < 0)
		warning(errno, "fork: ");
	if (!child2)
		child_two(fd, argv, envp);
	close (fd[0]);
	close (fd[1]);
	waitpid(child1, NULL, 0);
	waitpid(child2, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		write(2, "pipex: check args: ./pipex file1 cmd1 cmd2 file2\n", 49);
		exit(1);
	}
	pipex(argv, envp);
	return (0);
}
