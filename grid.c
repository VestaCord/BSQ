/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:04:14 by vtian             #+#    #+#             */
/*   Updated: 2025/04/08 15:24:09 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

char	*ft_create_grid(char *filename, t_map map)
{
	char	*grid;
	char	buffer;
	int		file;
	int		size;

	grid = malloc(sizeof(char) * map.cols * map.rows);
	file = open(filename, O_RDONLY);
	size = 0;
	while (read(file, &buffer, 1) > 0)
	{
		if (buffer == '\n')
			break;
	}
	while (read(file, &buffer, 1) > 0 && size < (map.cols * map.rows))
	{
		if (buffer != '\n')
			grid[size++] = buffer;
	}
	return (grid);
}

void	ft_print_grid(char *grid, t_map map)
{
	int	i;

	i = 0;
	while (i < (map.cols * map.rows))
	{
		write(1, grid + i, 1);
		if ((i + 1) % map.cols == 0)
			write (1, "\n", 1);
		i++;
	}
}