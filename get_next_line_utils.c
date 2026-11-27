/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilfran <guilfran@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 19:03:34 by guilfran          #+#    #+#             */
/*   Updated: 2026/10/07 19:06:12 by guilfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_lenchr(char *s, int mode)
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

char	*ft_strjoin(char *s1, char *s2)
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

char	*ft_line(char *s)
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

char	*ft_readline(char *line, char *stash, int fd)
{
	ssize_t	bytes;

	bytes = 1;
	while (ft_lenchr(line, 1) == 0 && bytes > 0)
	{
		bytes = read(fd, stash, BUFFER_SIZE);
		if (bytes < 0)
		{
			if (line)
			{
				free(line);
				line = NULL;
			}
			return (NULL);
		}
		stash[bytes] = '\0';
		line = ft_strjoin(line, stash);
	}
	return (line);
}
