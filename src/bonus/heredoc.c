/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 11:43:35 by mmendiol          #+#    #+#             */
/*   Updated: 2024/04/25 14:22:11 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	heredoc(char *args[])
{
	int		infile;
	char	*line;
	char	*delimiter;

	infile = open(TMP_FILE, O_WRONLY | O_CREAT, 0644);
	line = get_next_line(0);
	delimiter = ft_strjoin(args[2], "\n");
	while (line != NULL && !ft_strcmp(line, delimiter))
	{
		ft_putstr_fd(line, infile);
		free(line);
		line = get_next_line(0);
	}
	free(delimiter);
	if (line)
		free(line);
}
