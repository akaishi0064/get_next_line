/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chakaish <chakaish@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:33:17 by chakaish          #+#    #+#             */
/*   Updated: 2025/01/02 17:01:55 by chakaish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

static void free_buffer(char **buffer)
{
	if (*buffer != NULL)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

static char	*get_result(int n1_num, char **buffer_s)
static char	*rd_file(int fd, char **buffer_save, char *buf)
{
	size_t	count_byt;
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
		buf(bu









char	*get_next_line(int fd)
{
	static	char *save;
	char	*buf_baket;
	char	*result;

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

int	main ()
{
	int		fd;
	int		i;
	char	*s;

	fd = open("cat.txt", O_RDONRY);
	i = 0;
	while (i < 10)
	 {
		 s = get_next_line(fd);
		 printf("%s", s);
		 free(s);
		 i++;
	 }
	 close(fd);
	 return (0);
}

__attribute__((destructor))
static void destructor()
{
	system("leaks -q a.out");
}
