/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:17:08 by mmendiol          #+#    #+#             */
/*   Updated: 2024/04/17 14:05:58 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// void	ft_leaks(void)
// {
// 	system("leaks -q pipex");
// }
// atexit(ft_leaks);

void	show_error(char *str, char *cmd_file)
{
	char	*msg;

	msg = ft_strjoin(str, cmd_file);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	next_cmds(char **arg, char **env, int pid, int *fd)
{
	int	fd2[2];
	int	ac;
	int	i;

	i = 2;
	ac = 0;
	while (arg[ac])
		ac++;
	while (++i < (ac - 2))
	{
		if (pipe(fd2))
			show_error(PIPE, NULL);
		pid = fork();
		if (pid == -1)
			show_error(CHILD, NULL);
		if (pid == 0)
		{
			other_childs(fd, fd2);
			check_access(arg[i], env);
		}
		close(fd[READ_FD]);
		close(fd2[WRITE_FD]);
		fd[READ_FD] = fd2[READ_FD];
	}
	parent_bonus(arg, env, pid, fd);
}

int	main(int ac, char *av[], char *env[])
{
	int	fd[2];
	int	pid[2];
	int	status;

	if (ac >= 5)
	{
		if (pipe(fd))
			show_error(PIPE, NULL);
		pid[0] = fork();
		if (pid[0] == -1)
			show_error(CHILD, NULL);
		if (pid[0] == 0)
			first_child(av, env, fd);
		else
			next_cmds(av, env, pid[1], fd);
		waitpid(pid[0], NULL, 0);
		waitpid(pid[1], &status, 0);
	}
	else
		ft_putstr_fd(ARGUMENTS, 2);
	return (WEXITSTATUS(status));
}
