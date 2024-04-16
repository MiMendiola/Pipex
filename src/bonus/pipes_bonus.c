/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:00:35 by mmendiol          #+#    #+#             */
/*   Updated: 2024/04/16 19:30:37 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child(char **arguments, char **enviroment, int *fd)
{
	int	infile;

	infile = open(arguments[1], O_RDONLY);
	if (infile == -1)
		show_error(FILE, arguments[1]);
	dup2(infile, STDIN_FILENO);
	dup2(fd[WRITE_FD], STDOUT_FILENO);
	close(infile);
	close(fd[READ_FD]);
	close(fd[WRITE_FD]);
	check_access(arguments[2], enviroment);
}

void	parent_bonus(char **arguments, int ac, char **enviroment, int pid, int *fd)
{
	int	outfile;

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
