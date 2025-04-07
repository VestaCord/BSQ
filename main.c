#include "header.h"

int	main(int argc, char *argv[])
{
	t_map	*map;
	int		i;

	if (argc < 2)
	{
		// no file passed in, read single file from standard input
	}
	else
	{
		i = 1;
		while (argc-- > 1)//read each file except the program filename
		{
			//read each file
			map = map_check(argv[i]);
			if (map == NULL)
				write(1, "map error\n", 10);
			find_square(map);
			print_solution(map);
		}
	}
	return (0);
}
