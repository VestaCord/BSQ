/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:27:28 by vtian             #+#    #+#             */
/*   Updated: 2025/04/08 15:25:54 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int	ft_get_position(int row, int col, int size)
{
	int	position;

	position = row * size + col;
	return (position);
}

// no file passed in, read single file from standard input
int	main(int argc, char *argv[])
{
	t_map		map;
	char		*filename;
	char		*puzzle;
	char		*working;
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
	puzzle = ft_create_grid(filename, map);
	ft_print_grid(puzzle, map);
	free(puzzle);
	printf("emp=%c\nobs=%c\nful=%c\n", map.emp, map.obs, map.ful);
	printf("cols=%d\n", map.cols);
	printf("rows=%d\n", map.rows);
}
