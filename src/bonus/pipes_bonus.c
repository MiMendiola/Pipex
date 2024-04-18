/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:00:35 by mmendiol          #+#    #+#             */
/*   Updated: 2024/04/18 15:58:39 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	other_childs(int *fd, int *fd2)
{
	dup2(fd[READ_FD], STDIN_FILENO);
	dup2(fd2[WRITE_FD], STDOUT_FILENO);
	close(fd[WRITE_FD]);
	close(fd2[WRITE_FD]);
	close(fd2[READ_FD]);
}

void	connect_next_cmd(int *fd, int *fd2)
{
	close(fd[READ_FD]);
	close(fd2[WRITE_FD]);
	fd[READ_FD] = fd2[READ_FD];
}

void	first_child(char **arguments, char **enviroment, int *fd)
{
	int	infile;
	int	i;

	i = 1;
	if (!ft_strncmp(arguments[1], "here_doc", 8))
		i++;		
	infile = open(arguments[i++], O_RDONLY);
	if (infile == -1)
		show_error(FILE, arguments[--i]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[WRITE_FD], STDOUT_FILENO);
	close(infile);
	close(fd[READ_FD]);
	close(fd[WRITE_FD]);
	check_access(arguments[i], enviroment);
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
	if (!ft_strncmp(arg[1], "here_doc", 8))
		i++;
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
		connect_next_cmd(fd, fd2);
	}
	parent_bonus(arg, env, pid, fd);
}

void	parent_bonus(char **arguments, char **enviroment, int pid, int *fd)
{
	int	outfile;
	int	ac;

	ac = 0;
	while (arguments[ac])
		ac++;
	close(fd[WRITE_FD]);
	pid = fork();
	if (pid == -1)
		show_error(CHILD, NULL);
	if (pid == 0)
	{
		outfile = open(arguments[ac - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		dup2(fd[READ_FD], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(fd[READ_FD]);
		check_access(arguments[ac - 2], enviroment);
	}
	else
		close(fd[READ_FD]);
}
