

#include "fdf.h"

//TODO debug function: delete
void	print_array(char **arr)
{
	for (int i = 0 ; arr[i] ; i++)
		printf("%s\n", arr[i]);
}

/*
 * Increments path_idx variable to the first non-option-flag arg in argv.
 * Sets any valid option flags in the fdf state struct.
 */
static int	handle_option_flags(t_fdf *fdf, char **argv)
{
	char	*arg;

	fdf->path_idx = 1;
	while (argv[fdf->path_idx])
	{
		arg = argv[fdf->path_idx];
		if (arg[0] != '-')
			break ;
		if (ft_strequ(HELP_FLAG, arg))
			fdf->help = TRUE;
		if (ft_strequ(TEST_PARSER, arg))
			fdf->test_parser = TRUE;
		else
			return (print_error(FALSE, ERROR_INVALID_OPTION));
		(fdf->path_idx)++;
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc == 1)
		return (print_error(RETURN_SUCCESS, USAGE));
	ft_bzero((void *) &fdf, sizeof(t_fdf));
	if (!handle_option_flags(&fdf, argv))
		return (RETURN_ERROR);
	if (fdf.help)
		return (print_error(RETURN_SUCCESS, USAGE_LONG));
	if (!(argv[fdf.path_idx]))
		return (print_error(RETURN_SUCCESS, USAGE));
	if (!map_parser_control(&fdf, argv[fdf.path_idx]))
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
	if (!(fdf->test_parser))
		fdf_control()
	*/
	return (free_and_exit(&fdf, RETURN_SUCCESS));
}
