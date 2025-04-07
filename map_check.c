/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jia-lim <jia-lim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:43:04 by jia-lim           #+#    #+#             */
/*   Updated: 2025/04/07 16:43:28 by jia-lim          ###   ########.fr       */
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

int	obs_count_helper(char c, t_map *map, t_point *point, int *obs_count)
{
	if (c == map->emp || c == map->obs)
	{
		point->x++;
		if (c == map->obs)
			(*obs_count)++;
	}
	else if (c == '\n')
	{
		if (point->y == 0)
			map->cols = point->x;
		else if (point->x != map->cols)
			return (0);
		point->x = 0;
		point->y++;
	}
	else
		return (0);
	return (1);
}

int	get_obs_count(int fd, t_map *map)
{
	int		obs_count;
	int		col_count;
	char	c;
	t_point	point;

	obs_count = 0;
	col_count = 0;
	point.x = 0;
	point.y = 0;
	while (point.y < map->rows)
	{
		if (read(fd, &c, 1) <= 0)
			break ;
		if (obs_count_helper(c, map, &point, &obs_count) == 0)
			return (-1);
	}
	if (point.y == map->rows && read(fd, &c, 1) == 0)
		return (obs_count);
	return (-1);
}

t_map	*map_check(char *input_file)
{
	int		fd;
	t_map	*map;
	char	c;

	fd = open(input_file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = (t_map *)malloc(sizeof(t_map));
	map->rows = get_map_size(fd, &c);
	map->emp = get_map_eof(fd, &c);
	map->obs = get_map_eof(fd, &c);
	map->ful = get_map_eof(fd, &c);
	map->obs_count = get_obs_count(fd, map);
	close(fd);
	if (!map->rows || !map->emp || !map->obs || !map->ful || \
		map->obs_count == -1)
	{
		free(map);
		return (NULL);
	}
	return (map);
}

// int	main(int argc, char *argv[])
// {
// 	t_map	*map;
// 	if (argc < 2)
// 	{
// 		// no file passed in, read single file from standard input
// 	}
// 	else
// 	{
// 		map = map_check(argv[1]);
// 		if (!map)
// 			return 1;
// 		printf("emp=%c\nobs=%c\nful=%c\n", map->emp,map->obs,map->ful);
// 		printf("obs_count=%d\n", map->obs_count);
// 		printf("cols=%d\n", map->cols);
// 		printf("rows=%d\n", map->rows);
// 	}
// }