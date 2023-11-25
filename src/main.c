

#include "fdf.h"

//TODO debug function: delete
void	print_array(char **arr)
{
	for (int i = 0 ; arr[i] ; i++)
		printf("%s\n", arr[i]);
}

static int	map_path_idx(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] && argv[i][0] == '-')
		i++;
	return (i);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc == 1 || ft_strequ(argv[1], HELP_FLAG))
		return (print_error(RETURN_SUCCESS, USAGE));
	ft_bzero((void *) &fdf, sizeof(t_fdf));
	// parse map
	if (!map_parser_control(&fdf, *(argv + map_path_idx(argv))))
		return (free_and_exit(&fdf, RETURN_ERROR));
	
	t_coord	*current;
	current = fdf.coord_list;
	//print coords for testing
	while (current)
	{
		printf("x = %d | y = %d | z = %d\n", current->x, current->y, current->z);
		current = current->next;
	}
	// fdf starts...
	/*
	if (!ft_strequ(argv[1], TEST_PARSER)
		fdf_control()
	*/
	return (free_and_exit(&fdf, RETURN_SUCCESS));
}
