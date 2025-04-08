/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:27:28 by vtian             #+#    #+#             */
/*   Updated: 2025/04/08 16:44:29 by vtian            ###   ########.fr       */
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
// Returns solution row, col, size
// For debugging, add '0' to grid values so they can be printed
t_soln	ft_solve_square(char *working, char *puzzle, t_map map)
{
	int	row;
	int	col;
	t_soln soln;

	row = 0;
	soln.size = 0;
	while (row++ < map.rows)
	{
		col = 0;
		while (col++ < map.cols)
		{
			ft_set_grid(row, col, working, map, (ft_calculate_square(row, col, puzzle, map)));
			if (ft_get_grid(row, col, working, map) > soln.size)
			{
				soln.col = col;
				soln.row = row;
				soln.size = ft_get_grid(row, col, working, map);
			}
		}
	}
	return (soln);
}

// Inserts the largest square at the given position
void	ft_set_square(t_soln soln, char *puzzle, t_map map)
{
	int row;
	int	col;

	row = -1;
	while (row++ < soln.size)
	{
		col = -1;
		while (col++ < soln.size)
		{
			ft_set_grid(soln.row + row, soln.col + col, puzzle, map, map.ful);
		}
	}
}

// no file passed in, read single file from standard input
// LIMITATIONS max square size is 255 because it is stored in a char
// LIMITATIONS used int and unsigned int inconsistently so
// 	it might be weird if size approaches 2^31
// remember to check valgrind before every commit
// remember to remove all printf and norminette before submission
// remember to remove the '0' used for solution printing
// 	in ft_solve_square
int	main(int argc, char *argv[])
{
	t_map		map;
	t_soln		soln;
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
	soln = ft_solve_square(working, puzzle, map);
	ft_print_grid(puzzle, map);
	printf("emp=%c\nobs=%c\nful=%c\n", map.emp, map.obs, map.ful);
	printf("cols=%d\n", map.cols);
	printf("rows=%d\n", map.rows);
	printf("Solution is (%d, %d) of size %d\n", soln.row, soln.col, soln.size);
	ft_set_square(soln, puzzle, map);
	ft_print_grid(puzzle, map);
	free(puzzle);
	free(working);
}
