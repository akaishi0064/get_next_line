/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakaish <chakaish@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:33:17 by chakaish          #+#    #+#             */
/*   Updated: 2025/02/03 13:36:46 by chakaish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_buffer(char **buffer)
{
	if (*buffer != NULL)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

static char	*get_result(int n1_num, char **buffer_s)
{
	char	*result;
	char	*tmp;

	tmp = NULL;
	if (n1_num <= 0)
	{
		if (**buffer_s == '\0')
		{
			free(*buffer_s);
			*buffer_s = NULL;
			return (NULL);
		}
		result = *buffer_s;
		*buffer_s = NULL;
		return (result);
	}
	tmp = ft_substr(*buffer_s, n1_num, BUFFER_SIZE);
	result = *buffer_s;
	result[n1_num] = '\0';
	*buffer_s = tmp;
	return (result);
}

static char	*rd_file(int fd, char **buffer_save, char *buf)
{
	ssize_t	count_byt;
	char	*tmp;

	tmp = NULL;
	count_byt = 0;
	while (ft_strchr(*buffer_save, '\n') == NULL)
	{
		count_byt = read(fd, buf, BUFFER_SIZE);
		if (count_byt < 0)
		{
			free_buffer(buffer_save);
			return (NULL);
		}
		if (count_byt == 0)
			return (get_result(count_byt, buffer_save));
		buf[count_byt] = '\0';
		tmp = ft_strjoin(*buffer_save, buf);
		if (tmp == NULL)
			return (free_buffer(buffer_save), NULL);
		free_buffer(buffer_save);
		*buffer_save = tmp;
	}
	return (get_result((ft_strchr(*buffer_save, '\n') - *buffer_save) + 1,
			buffer_save));
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf_baket;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf_baket = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buf_baket == NULL)
		return (NULL);
	if (!save)
	{
		save = ft_strdup("");
		if (save == NULL)
		{
			free(buf_baket);
			free(save);
			return (NULL);
		}
	}
	result = rd_file(fd, &save, buf_baket);
	free_buffer(&buf_baket);
	return (result);
}

// int	main(void)
// {
// 	int		fd;
// 	int		i;
// 	char	*s;

// 	fd = open("cat.txt", O_RDONLY);
// 	i = 0;
// 	while ((s=get_next_line(1))!=NULL)
// 	{
// 		printf("%s", s);
// 		free(s);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q a.out");
// }
