/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amansir <amansir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:28:34 by amansir           #+#    #+#             */
/*   Updated: 2025/12/13 23:34:58 by amansir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	if (s1 != NULL)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	if (s2 != NULL)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (free(s1),free(s2), NULL);
	if (s1)
		ft_memcpy(joined, s1, len1);
	if (s2)
		ft_memcpy(joined + len1, s2, len2);
	joined[len1 + len2] = '\0';
	free(s1);
	return (joined);
}

char	*extract_line(char **buffer)
{
	char	*line;
	char	*new_buffer;
	char	*nl_pos;
	size_t	len;

	if (!*buffer || **buffer == '\0')
		return (NULL);
	nl_pos = ft_strchr(*buffer, '\n');
	if (nl_pos)
	{
		len = nl_pos - *buffer + 1;
		line = ft_strndup(*buffer, len);
		new_buffer = ft_strdup(nl_pos + 1);
		free(*buffer);
		*buffer = new_buffer;
	}
	else
	{
		line = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*the_reader(int fd, char *buffer)
{
	char	*temp;
	ssize_t	bytes_read;

	temp = malloc((size_t)BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	while (!ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(temp);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		temp[bytes_read] = '\0';
		buffer = ft_strjoin_free(buffer, temp);
		if (!buffer)
			return (NULL);
	}
	return (free(temp), buffer);
}

char	*get_next_line(int fd)
{
	static char	*static_buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_buff = the_reader(fd, static_buff);
	if (!static_buff || *static_buff == '\0')
	{
		free(static_buff);
		static_buff = NULL;
		return (NULL);
	}
	line = extract_line(&static_buff);
	return (line);
}
