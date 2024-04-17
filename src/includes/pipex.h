/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:18:19 by mmendiol          #+#    #+#             */
/*   Updated: 2024/04/17 14:01:41 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../libft/includes/libft.h"
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* ================= PIPE ENDS =================== */
# define READ_FD 0
# define WRITE_FD 1

/* ================== MESSAGES =================== */
# define FILE "zsh: no such file or directory: "
# define COMMAND "zsh: command not found: "
# define ARGUMENTS "Error: bad number of arguments\n"
# define CHILD "child error"
# define PIPE "pipe error"
# define PATH "PATH="

/* =================== PIPEX ===================== */
void	show_error(char *str, char *cmd_file);

/* =================== PIPES ===================== */
void	child(char **arguments, char **enviroment, int *fd);
void	parent(char **arguments, char **enviroment, int pid, int *fd);

/* =================== CHECKS ==================== */
char	*check_path(char **flags_cmd, char **enviroment);
int		check_access(char *argument, char **enviroment);

/* ================= PIPES BONUS ================== */
void	first_child(char **arguments, char **enviroment, int *fd);
void	other_childs(int *fd, int *fd2);
void	parent_bonus(char **arguments, char **enviroment, int pid, int *fd);

/* ============== SETTINGS COLORS ================ */
# define BLACK "\x1B[30m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1B[37m"
# define ORANGE "\x1B[38;2;255;128;0m"
# define ROSE "\x1B[38;2;255;151;203m"
# define LBLUE "\x1B[38;2;53;149;240m"
# define LGREEN "\x1B[38;2;17;245;120m"
# define GRAY "\x1B[38;2;176;174;174m"
# define CLEAR "\x1b[0m"

/* ======== SETTINGS BACKGROUND COLORS ========== */
# define BG_BLACK "\x1B[40m"
# define BG_RED "\x1B[41m"
# define BG_GREEN "\x1B[42m"
# define BG_YELLOW "\x1B[43m"
# define BG_BLUE "\x1B[44m"
# define BG_MAGENTA "\x1B[45m"
# define BG_CYAN "\x1B[46m"
# define BG_WHITE "\x1B[47m"
# define BG_ORANGE "\x1B[48;2;255;128;0m"
# define BG_LBLUE "\x1B[48;2;53;149;240m"
# define BG_LGREEN "\x1B[48;2;17;245;120m"
# define BG_GRAY "\x1B[48;2;176;174;174m"
# define BG_ROSE "\x1B[48;2;255;151;203m"

#endif