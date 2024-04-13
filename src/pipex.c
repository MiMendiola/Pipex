/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:17:08 by mmendiol          #+#    #+#             */
/*   Updated: 2024/04/13 19:42:56 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	ft_leaks(void)
{
	system("leaks -q pipex");
}

void	show_error(char *str, char *cmd_file)
{
    char *msg;

    msg = ft_strjoin(str, cmd_file);
    ft_putstr_fd(msg, 2);
    ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

char    *check_path(char **flags_cmd, char **enviroment)
{
    char **path;
    char *command;
    char *aux;
    int i;
    
    i = 0;
    while (ft_strncmp(enviroment[i], "PATH=", 5))
        i++;
    path = ft_split(enviroment[i] + 5, ':');
    i = 0;
    while (path[i])
    {
        aux = ft_strjoin(path[i++], "/");
        command = ft_strjoin(aux, flags_cmd[0]);
        free(aux);
        if (access(command, F_OK | X_OK) == 0)
            return (command);
        free(command);
    }
    free_matrix(path);
    return (NULL);
}

int check_access(char *argument, char **enviroment)
{
    char **flags_cmd;
    char *command;

    flags_cmd = ft_split(argument, ' ');
    command = check_path(flags_cmd, enviroment);

    if (command == NULL)
        show_error("zsh: command not found: ", argument);
    if (access(command, F_OK | X_OK) == 0)
        execve(command, flags_cmd, enviroment);
    free_matrix(flags_cmd);
    return (-1);
}

void    child(char **arguments, char **enviroment, int *fd)
{
	int fd1;
	
	fd1 = open(arguments[1], O_RDONLY);
	if (fd1 == -1)
        show_error("zsh: no such file or directory: ", arguments[1]);
    dup2(fd1, STDIN_FILENO);
    dup2(fd[WRITE_FD], STDOUT_FILENO);
    close(fd1);
    close(fd[READ_FD]);
    close(fd[WRITE_FD]);
    check_access(arguments[2], enviroment);
    wait(NULL);
}

void    parent(char **arguments, char **enviroment, int *fd)
{
	int fd2;
	int pid;
	
	close(fd[WRITE_FD]);
	pid = fork();
    if (pid == -1)
        show_error("child error", NULL);
	if (pid == 0)
	{
		fd2 = open(arguments[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		dup2(fd[READ_FD], STDIN_FILENO);
		dup2(fd2, STDOUT_FILENO);
		close(fd[READ_FD]);
		check_access(arguments[3], enviroment);
	}
	else
		close(fd[READ_FD]);
    wait(NULL);
}

int main(int ac, char *av[], char *env[])
{
    int fd[2];
    int pid;

    //atexit(ft_leaks);
    if (ac == 5)
    {
        if (pipe(fd))
            show_error("pipe error", NULL);
        pid = fork();
        if (pid == -1)
            show_error("child error", NULL);
        if (pid == 0)
            child(av, env, fd);
        else
            parent(av, env, fd);
    }
    else
        ft_putstr_fd("Error: bad number of arguments\n", 2);
    return (0);
}
