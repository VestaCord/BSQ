/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:43:04 by jia-lim           #+#    #+#             */
/*   Updated: 2025/04/07 20:20:21 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "bsq.h"

// Returns the number of lines from information on the map
// Moves fileptr (c) to next char (empty)
unsigned int	get_map_size(int fd, char *c)
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
// moves fileptr (c) to next char (obs/full)
char	get_map_eof(int fd, char *c)
{
	char	eof;

	eof = 0;
	if (*c >= 32 && *c <= 126)
		eof = *c;
	if (*c != '\n')
	{
		if (read(fd, c, 1) <= 0)
			eof = 0;
	}
	return (eof);
}

// returns map if rectangular, legend is full, 
t_map	ft_read_map(int fd)
{
	t_map	map;
	char	c;

	map.cols = 0;
	map.rows = get_map_size(fd, &c);
	map.emp = get_map_eof(fd, &c);
	map.obs = get_map_eof(fd, &c);
	map.ful = get_map_eof(fd, &c);
	close(fd);
	return (map);
}

// returns failure if invalid map
int	ft_check_map(t_map map)
{
	if (!map.rows || !map.emp || !map.obs || !map.ful)
		return (E_FAILURE);
	return (E_SUCCESS);
}

// no file passed in, read single file from standard input
int	main(int argc, char *argv[])
{
	t_map	map;
	int		fd;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (1);
	if (fd < 0)
		return (1);
	map = ft_read_map(fd);
	if (ft_check_map(map) == E_FAILURE)
	{
		write(1, "map error\n", 11);
	}
	printf("emp=%c\nobs=%c\nful=%c\n", map.emp, map.obs, map.ful);
	printf("cols=%d\n", map.cols);
	printf("rows=%d\n", map.rows);
}
