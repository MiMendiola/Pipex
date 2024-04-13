/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendiol <mmendiol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 18:18:19 by mmendiol          #+#    #+#             */
/*   Updated: 2024/04/11 18:49:43 by mmendiol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../libft/includes/libft.h"
# include "./defines.h"
# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// #define READ_FD 0
// #define WRITE_FD 1

#ifndef READ_FD
# define READ_FD 0 /* PIPE EXTREMO DE LECTURA */
#endif

#ifndef WRITE_FD
# define WRITE_FD 1 /* PIPE EXTREMO DE ESCRITURA */
#endif

#ifndef FILE_NAME
# define FILE_NAME "out.txt" /* NOMBRE DEL ARCHIVO DND SE GUARDA LA INFO */
#endif

#endif