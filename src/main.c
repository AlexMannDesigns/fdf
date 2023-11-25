

#include "fdf.h"

/*
 * All-purpose error message printer
 * Prints 'msg' to STDERR, followed by NL, and then returns 'ret'
 */
int	print_error(int ret, char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (ret);
}

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

	// struct...?
	if (argc == 1 || ft_strequ(argv[1], HELP_FLAG))
		return (print_error(RETURN_ERROR, USAGE));
	ft_bzero((void *) &fdf, sizeof(t_fdf));
	// parse map
	if (!map_parser_control(&fdf, *(argv + map_path_idx(argv))))
		return (RETURN_ERROR);
	// fdf starts...
	/*
	if (!ft_strequ(argv[1], TEST_PARSER)
		fdf_control()
	*/
	return (RETURN_SUCCESS);
}
