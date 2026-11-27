/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilfran <guilfran@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 16:26:53 by guilfran          #+#    #+#             */
/*   Updated: 2026/10/07 19:04:33 by guilfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*line[1024];
	char		*stash;
	char		*result;
	char		*temp;

	stash = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (stash == NULL || BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
		return (free(stash), NULL);
	line[fd] = ft_readline(line, stash, fd);
	if (line[fd] == NULL)
		return (NULL);
	result = ft_line(line[fd]);
	temp = ft_strjoin(NULL, &line[fd][ft_lenchr(result, 0)]);
	free(line[fd]);
	line[fd] = temp;
	return (free(stash), result);
}

// int main(void)
// {
//     int     fd1;
//     int     fd2;
//     char    *linea = NULL;
//     char    *linea2 = NULL;
//     int     active1 = 1;
//     int     active2 = 1;

//     fd1 = open("prueba1.txt", O_RDONLY);
//     fd2 = open("prueba2.txt", O_RDONLY);
//     if (fd1 == -1 || fd2 == -1)
//     {
//         printf("Error al abrir el archivo\n");
//         return (1);
//     }

//     // Bucle para leer ambos alternadamente de forma segura
//     while (active1 || active2)
//     {
//         if (active1)
//         {
//             linea = get_next_line(fd1);
//             if (linea != NULL)
//             {
//                 printf("FD1: %s", linea);
//                 free(linea);
//             }
//             else
//                 active1 = 0; // Este archivo ya terminó
//         }

//         if (active2)
//         {
//             linea2 = get_next_line(fd2);
//             if (linea2 != NULL)
//             {
//                 printf("FD2: %s", linea2);
//                 free(linea2);
//             }
//             else
//                 active2 = 0; // Este archivo ya terminó
//         }
//     }

//     close(fd1);
//     close(fd2);
//     return (0);
// }