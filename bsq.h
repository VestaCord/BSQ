/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:43:30 by vtian             #+#    #+#             */
/*   Updated: 2025/04/08 16:24:09 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# define E_FAILURE -1
# define E_SUCCESS 1 
# define F_STDIN "/dev/stdin"
# define F_NULL "/dev/null"

typedef struct s_map
{
	char			emp;
	char			obs;
	char			ful;
	unsigned int	rows;
	unsigned int	cols;
}				t_map;

typedef struct s_soln
{
	int	size;
	int	row;
	int	col;
}				t_soln;

int	ft_check_map(char *filename, t_map map);
t_map	ft_read_map(char *filename);

char	ft_get_grid(int row, int col, char *grid, t_map map);
void	ft_set_grid(int row, int col, char *grid, t_map map, char c);
char	*ft_create_grid(char *filename, t_map map);
void	ft_print_grid(char *grid, t_map map);

#endif