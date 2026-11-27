/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilfran <guilfran@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 16:26:53 by guilfran          #+#    #+#             */
/*   Updated: 2026/10/07 19:03:31 by guilfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*line;
	char		*stash;
	char		*result;
	char		*temp;

	stash = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (stash == NULL || BUFFER_SIZE <= 0 || fd < 0)
		return (free(stash), NULL);
	line = ft_readline(line, stash, fd);
	if (!line)
		return (free(stash), NULL);
	result = ft_line(line);
	temp = ft_strjoin(NULL, &line[ft_lenchr(result, 0)]);
	free(line);
	line = temp;
	return (free(stash), result);
}

// int  main(void)
// {
//     int     fd;
//     char    *linea;

//     fd = open("prueba1.txt", O_RDONLY);
//     if (fd == -1)
//     {
//         printf("Error al abrir el archivo\n");
//         return (1);
//     }
//     while ((linea = get_next_line(fd)) != NULL)
//     {
//         printf("%s", linea);
//         free(linea);
//     }
//     close(fd);
//     return (0);
// }
