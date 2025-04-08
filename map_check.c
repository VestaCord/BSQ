/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:43:04 by jia-lim           #+#    #+#             */
/*   Updated: 2025/04/08 13:48:05 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "bsq.h"

// Returns the number of lines from information on the map
// Moves fileptr (c) to next char (empty)
unsigned int	ft_get_rows(int fd, char *c)
{
	unsigned int	size;

	size = 0;
	while (1)
	{
		if (read(fd, c, 1) <= 0)
			break ;
		if (*c >= '0' && *c <= '9')
		{
			size *= 10;
			size += *c - '0';
		}
		else
			break ;
	}
	return (size);
}

// returns c if printable
// returns 0 if newline or invalid read
// moves fileptr (c) to next char (obs/full/newline)
char	ft_get_map_key(int fd, char *c)
{
	char	key;

	key = 0;
	if (*c >= 32 && *c <= 126)
		key = *c;
	if (*c != '\n')
	{
		if (read(fd, c, 1) <= 0)
			key = 0;
	}
	return (key);
}

// returns cols of first row
// returns 0 if non newline after legend
unsigned int	ft_get_cols(int fd, char *c)
{
	int	cols;

	cols = 0;
	if (*c != '\n')
		return (cols);
	while (read(fd, c, 1) > 0)
	{
		if (*c == '\n')
			return (cols);
		if (*c >= 32 && *c <= 126)
			cols++;
	}
	return (0);
}

// returns map with 0 for legends that were not found
// moves from row, to emp obs ful, to newline, then cols
t_map	ft_read_map(char *filename)
{
	t_map	map;
	int		fd;
	char	c;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		map.rows = 0;
		map.emp = 0;
		map.obs = 0;
		map.ful = 0;
		map.cols = 0;
		return (map);
	}
	map.rows = ft_get_rows(fd, &c);
	map.emp = ft_get_map_key(fd, &c);
	map.obs = ft_get_map_key(fd, &c);
	map.ful = ft_get_map_key(fd, &c);
	map.cols = ft_get_cols(fd, &c);
	close(fd);
	return (map);
}

// reads to start of map, then starts checking
// returns failure if inconsistent cols, missing keys, invalid key
// current only returns error for stdin if \n\n instead of just \n
int	ft_check_map(char *filename, t_map map)
{
	int				fd;
	unsigned int	cols;
	char			c;

	if (!map.rows || !map.cols || !map.emp || !map.obs || !map.ful)
		return (E_FAILURE);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (E_FAILURE);
	cols = 0;
	while (c != '\n')
		read(fd, &c, 1);
	while (read(fd, &c, 1) > 0)
	{
		if ((c != map.emp && c != map.obs && c != map.ful && c
		&& c != '\n') || ((c == '\n') && cols++ != map.cols))
		{
			close(fd);
			return (E_FAILURE);
		}
		cols++;
		if (c == '\n')
			cols = 0;
	}
	close(fd);
	return (E_SUCCESS);
}

// no file passed in, read single file from standard input
int	main(int argc, char *argv[])
{
	t_map		map;
	char		*filename;
	const char	*filename_default = "/dev/stdin";

	if (argc == 1)
		filename = (char *)filename_default;
	else if (argc == 2)
		filename = argv[1];
	else
		return (1);
	map = ft_read_map(filename);
	if (ft_check_map(filename, map) == E_FAILURE)
	{
		write(1, "map error\n", 11);
		return (1);
	}
	printf("emp=%c\nobs=%c\nful=%c\n", map.emp, map.obs, map.ful);
	printf("cols=%d\n", map.cols);
	printf("rows=%d\n", map.rows);
}
