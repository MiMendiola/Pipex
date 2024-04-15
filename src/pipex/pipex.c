/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:17:08 by mmendiol          #+#    #+#             */
/*   Updated: 2024/04/15 20:34:50 by mmendiol         ###   ########.fr       */
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

int	main(int ac, char *av[], char *env[])
{
	int	fd[2];
	int	pid[2];
	int	status;

	if (ac == 5)
	{
		if (pipe(fd))
			show_error(PIPE, NULL);
		pid[0] = fork();
		if (pid[0] == -1)
			show_error(CHILD, NULL);
		if (pid[0] == 0)
			child(av, env, fd);
		else
			parent(av, env, pid[1], fd);
		waitpid(pid[0], NULL, 0);
		waitpid(pid[1], &status, 0);
	}
	else
		ft_putstr_fd(ARGUMENTS, 2);
	return (WEXITSTATUS(status));
}
