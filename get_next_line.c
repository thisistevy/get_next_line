/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iung <iung@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 09:27:21 by iung              #+#    #+#             */
/*   Updated: 2022/12/23 16:34:27 by iung             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// read renvoie: 0 si count vaut 0, indefini si count > SIZEMAX
// -1 si read echoue,
// sinon le nombre d'octets lu (ex 0 a la fin du fichier)
// read(fd, void *buf, size_t count);

// utiliser strjoin - free S1 et remplace par nouveau
// je lis et je stock par x buffer jusqu'a \n(strchr) ou read = 0
// strjoin rejoin les buffer entre eux
// retourner toute la ligne jusqu'au \n ou fin de ficher (read = 0)
// malloc string de bonne taille
// prendre le reste apres le \n et strjoin avec le reste

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
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stock = ft_readnstore(stock, fd);
	if (!stock)
		return (NULL);
	line = ft_readline(stock);
	stock = ft_buffstock(stock);
	return (line);
}

// int	main(void)
// {
// 	char *line;
// 	int	fd;
// 	int i;

// 	i = 0;
// 	fd = open("test.txt", O_RDONLY);
// 	while(i < 1)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// }