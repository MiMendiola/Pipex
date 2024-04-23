/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:17:08 by mmendiol          #+#    #+#             */
/*   Updated: 2024/04/23 15:36:00 by mmendiol         ###   ########.fr       */
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

int	wait_childs(int *status, int pid)
{
	int	final_status;
	pid_t waited;

	final_status = 0;
	while (1)
	{
		waited = waitpid(-1, status, 0);
		if (waited == -1)
			break;
		if (waited == pid)
			final_status = WEXITSTATUS(*status);
	}
	return (final_status);
}



int	main(int ac, char *av[], char *env[])
{
	int	fd[2];
	int	pid;
	int	status;
	int	final_status;

	final_status = 0;
	if (ac >= 5)
	{
		if (!ft_strcmp(av[1], HERE_DOC))
			
		if (pipe(fd))
			show_error(PIPE, NULL);
		pid = fork();
		if (pid == -1)
			show_error(CHILD, NULL);
		if (pid == 0)
			first_child(av, env, fd);
		else
			next_cmds(av, env, &pid, fd);
		final_status = wait_childs(&status, pid);
	}
	else
		ft_putstr_fd(ARGUMENTS, 2);
	return (final_status);
}
