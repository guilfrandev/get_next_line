/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilfran <guilfran@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 16:26:53 by guilfran          #+#    #+#             */
/*   Updated: 2026/10/07 12:55:16 by guilfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	s1 = malloc(i + 2 * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	i = -1;
	while (s[++i] != '\0' && s[i] != '\n')
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
	static char	*line;
	char		*stash;
	char		*result;
	char		*temp;
	ssize_t		bytes;

	stash = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (stash == NULL || BUFFER_SIZE <= 0 || fd < 0)
		return (free(stash), NULL);
	bytes = 1;
	while (ft_lenchr(line, 1) == 0 && bytes > 0)
	{
		bytes = read(fd, stash, BUFFER_SIZE);
		if (bytes < 0)
			return (free(stash), NULL);
		stash[bytes] = '\0';
		line = ft_strjoin(line, stash);
	}
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
