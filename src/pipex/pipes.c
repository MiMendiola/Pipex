/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:00:35 by mmendiol          #+#    #+#             */
/*   Updated: 2024/09/04 16:05:41 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child(char **arguments, char **enviroment, int *fd)
{
	int	infile;

	infile = open(arguments[1], O_RDONLY);
	if (infile == -1)
	{
		close(fd[READ_FD]);
		close(fd[WRITE_FD]);
		show_error(FILE, arguments[1]);
	}
	dup2(infile, STDIN_FILENO);
	dup2(fd[WRITE_FD], STDOUT_FILENO);
	close(infile);
	close(fd[READ_FD]);
	close(fd[WRITE_FD]);
	check_access(arguments[2], enviroment);
}

void	parent(char **arguments, char **enviroment, int *pid, int *fd)
{
	int	outfile;

	close(fd[WRITE_FD]);
	*pid = fork();
	if (*pid == -1)
		show_error(CHILD, NULL);
	if (*pid == 0)
	{
		outfile = open(arguments[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (outfile < 0)
		{
			close(fd[READ_FD]);
			close(fd[WRITE_FD]);
			show_error(FILE, arguments[4]);
		}
		dup2(fd[READ_FD], STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		close(fd[READ_FD]);
		close(outfile);
		check_access(arguments[3], enviroment);
	}
	else
		close(fd[READ_FD]);
}
