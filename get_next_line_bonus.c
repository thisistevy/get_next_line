/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iung <iung@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:15:47 by iung              #+#    #+#             */
/*   Updated: 2022/12/23 16:35:36 by iung             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_buffjoin(const char *s1, const char *s2)
{
	int		i;
	int		j;
	int		size;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 | !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
		str[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_readline(char *stock)
{
	char	*str;
	int		len;

	len = 0;
	if (!stock[len])
		return (NULL);
	while (stock[len] && stock[len] != '\n')
		len++;
	str = malloc(sizeof(char) * len + 2);
	if (!str)
		return (NULL);
	len = 0;
	while (stock[len] && stock[len] != '\n')
	{
		str[len] = stock[len];
		len++;
	}
	if (stock[len] && stock[len] == '\n')
		str[len++] = '\n';
	str[len] = '\0';
	return (str);
}

char	*ft_buffstock(char *stock)
{
	char	*str;
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		free(stock);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(stock) - i + 1));
	if (!str)
		return (NULL);
	i++;
	while (stock[i])
		str[n++] = stock[i++];
	str[n] = '\0';
	free(stock);
	return (str);
}

char	*ft_readnstore(char *stock, int fd)
{
	char	*buf;
	int		bytes;

	bytes = 1;
	if (!stock)
		stock = ft_calloc(1, 1);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buf);
			free(stock);
			return (NULL);
		}
		buf[bytes] = '\0';
		stock = ft_free(stock, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*stock[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stock[fd] = ft_readnstore(stock[fd], fd);
	if (!stock[fd])
		return (NULL);
	line = ft_readline(stock[fd]);
	stock[fd] = ft_buffstock(stock[fd]);
	return (line);
}

// int	main(void)
// {
// 	char *line;
// 	int	fd;
// 	int fd2;
// 	int i;

// 	i = 0;
// 	fd = open("test.txt", O_RDONLY);
// 	fd2 = open("bible.txt", O_RDONLY);
// 	while(i < 1)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd2);
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// }