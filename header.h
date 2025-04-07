#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# define GRID_BFFER 1024
typedef struct s_map
{
	char			emp;
	char			obs;
	char			ful;
	// unsigned int	obs_count;
	unsigned int	rows;
	unsigned int	cols;
}				t_map;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

#endif
