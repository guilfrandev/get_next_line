/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilfran <guilfran@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 16:26:53 by guilfran          #+#    #+#             */
/*   Updated: 2026/10/07 14:02:04 by guilfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_lenchr(char *s, int mode)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (mode == 0)
	{
		while (s[i] != '\0')
			i++;
	}
	if (mode == 1)
	{
		while (s[i] != '\0')
		{
			if (s[i] == '\n')
				return (1);
			i++;
		}
		i = 0;
	}
	return (i);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 && ft_lenchr(s2, 0) == 0)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(1);
		if (s1 == NULL)
			return (NULL);
		s1[0] = '\0';
	}
	s3 = malloc((ft_lenchr(s1, 0) + ft_lenchr(s2, 0) + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		s3[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		s3[i + j] = s2[j];
	s3[i + j] = '\0';
	free(s1);
	return (s3);
}

static char	*ft_line(char *s)
{
	int		i;
	char	*s1;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	s1 = malloc((i + 2) * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	i = -1;
	while (s[++i] != '\n' && s[i] != '\0')
		s1[i] = s[i];
	if (s[i] == '\n')
	{
		s1[i] = '\n';
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*get_next_line(int fd)
{
	static char	*line[1024];
	char		*stash;
	char		*result;
	char		*temp;
	ssize_t		bytes;

	stash = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (stash == NULL || BUFFER_SIZE <= 0 || fd < 0 || fd >= 1024)
		return (free(stash), NULL);
	bytes = 1;
	while (ft_lenchr(line[fd], 1) == 0 && bytes > 0)
	{
		bytes = read(fd, stash, BUFFER_SIZE);
		if (bytes < 0)
			break ;
		stash[bytes] = '\0';
		line[fd] = ft_strjoin(line[fd], stash);
	}
	if (bytes < 0 || !line[fd] || line[fd][0] == '\0')
        return (free(line[fd]), line[fd] = NULL, free(stash), NULL);
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