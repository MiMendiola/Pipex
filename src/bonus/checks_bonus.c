/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:58:56 by mmendiol          #+#    #+#             */
/*   Updated: 2024/04/15 20:35:03 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*check_path(char **flags_cmd, char **enviroment)
{
	char	**path;
	char	*command;
	char	*aux;
	int		i;

	i = 0;
	while (ft_strncmp(enviroment[i], PATH, 5))
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

int	check_access(char *argument, char **enviroment)
{
	char	**flags_cmd;
	char	*command;

	flags_cmd = ft_split(argument, ' ');
	if (!ft_strncmp(flags_cmd[0], "/", 1))
		command = flags_cmd[0];
	else
		command = check_path(flags_cmd, enviroment);
	if (command == NULL)
		show_error(COMMAND, argument);
	if (access(command, F_OK | X_OK) == 0)
		execve(command, flags_cmd, enviroment);
	else
		show_error(COMMAND, argument);
	free_matrix(flags_cmd);
	return (-1);
}
