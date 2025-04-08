/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:27:28 by vtian             #+#    #+#             */
/*   Updated: 2025/04/08 16:20:17 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

// 1-Indexed Grid
// Returns the largest square which can be created
// with its upper left corner at the current position
// while empty tiles in row, set size based on width,
// if first tile checked in row is obs, set size to height
int	ft_calculate_square(int row, int col, char *puzzle, t_map map)
{
	int max;
	int	tmp;
	int	i_row;
	int	j_col;

	i_row = 0;
	j_col = 0;
	max = 0;
	while ((ft_get_grid(row + i_row, col + j_col, puzzle, map) == map.emp) && (i_row < max || max == 0))
	{
		while ((ft_get_grid(row + i_row, col + j_col, puzzle, map) == map.emp) && ((j_col < max) || (max == 0)))
			j_col++;
		max = j_col;
		i_row++;
		j_col = 0;
	}
	if (i_row < max)
		max = i_row;
	return (max);
}

// Populates the working grid according to largest possible squares
void	ft_solve_square(char *working, char *puzzle, t_map map)
{
	int	row;
	int	col;

	row = 0;
	while (row++ < map.rows)
	{
		col = 0;
		while (col++ < map.cols)
		ft_set_grid(row, col, working, map, (ft_calculate_square(row, col, puzzle, map) + '0'));
	}
}

// Inserts the largest square at the given position
void	ft_print_square(int row, int col, char *puzzle, t_map map)
{
	;
}

// no file passed in, read single file from standard input
// remember to check valgrind before every commit
// remember to remove all printf and norminette before submission
int	main(int argc, char *argv[])
{
	t_map		map;
	char		*filename;
	char		*puzzle;
	char		*working;

	if (argc == 1)
		filename = F_STDIN;
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
	working = ft_create_grid(F_NULL, map);
	printf("Size on (1,5) is %d\n", ft_calculate_square(1, 5, puzzle, map));
	ft_solve_square(working, puzzle, map);
	ft_print_grid(puzzle, map);
	ft_print_grid(working, map);
	free(puzzle);
	free(working);
	printf("emp=%c\nobs=%c\nful=%c\n", map.emp, map.obs, map.ful);
	printf("cols=%d\n", map.cols);
	printf("rows=%d\n", map.rows);
}
