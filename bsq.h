/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtian <vtian@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:43:30 by vtian             #+#    #+#             */
/*   Updated: 2025/04/07 20:22:25 by vtian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# define GRID_BFFER 1024
# define E_FAILURE -1
# define E_SUCCESS 1 

typedef struct s_map
{
	char			emp;
	char			obs;
	char			ful;
	unsigned int	rows;
	unsigned int	cols;
}				t_map;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

#endif