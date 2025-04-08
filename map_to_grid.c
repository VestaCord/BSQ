/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:43:04 by jia-lim           #+#    #+#             */
/*   Updated: 2025/04/08 14:49:46 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

int	check_char(char c, t_map map)
{
	if (c == map.emp)
		return (0);
	else if (c == map.obs)
		return (1);
	return (-1);
}

int	get_grid(int fd, t_map *map, int *grid)
{
	char			c;
	t_point			point;
	unsigned int	i;

	point.x = 0;
	point.y = 0;
	i = 0;
	while (point.y < map->rows)
	{
		if (read(fd, &c, 1) <= 0)
			break ;
		if (c == '\n')
		{
			if (point.y++ == 0)
				map->cols = point.x;
			else if (point.x != map->cols)
				return (0);
			point.x = 0;
		}
		else
		{
			grid[i++] = check_char(c, *map);
			point.x++;
		}
	}
	return (read(fd, &c, 1) == 0);
}

t_map	*map_check(char *input_file)
{
	int		fd;
	t_map	*map;
	char	c;
	int		*grid;
	int		result;

	fd = open(input_file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = (t_map *)malloc(sizeof(t_map));
	grid = (int *)malloc(sizeof(int) * GRID_BFFER);
	map->rows = get_map_size(fd, &c);
	map->emp = get_map_eof(fd, &c);
	map->obs = get_map_eof(fd, &c);
	map->ful = get_map_eof(fd, &c);
	result = get_grid(fd, map, grid);
	close(fd);
	if (!map->rows || !map->emp || !map->obs || !map->ful || \
		result == 0)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

int	main(int argc, char *argv[])
{
	t_map	*map;
	if (argc < 2)
	{
		// no file passed in, read single file from standard input
	}
	else
	{
		map = map_check(argv[1]);
		if (!map)
			return 1;
		printf("emp=%c\nobs=%c\nful=%c\n", map->emp,map->obs,map->ful);
		printf("obs_count=%d\n", map->obs_count);
		printf("cols=%d\n", map->cols);
		printf("rows=%d\n", map->rows);
	}
}