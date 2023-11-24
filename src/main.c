

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

int	map_parser_control(t_fdf *fdf, char **argv)
{
	int	i;
	// int	fd;

	(void) fdf;
	i = 1;
	while (argv[i] && argv[i][0] == '-')
		i++;

	// check path points to a file, with extention '.fdf'
	// fd = open() ??


	// read line of map into buffer
	// check line length
	// check all chars numeric or whitespace
	return (RETURN_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	// struct...?
	if (argc == 1 || ft_strequ(argv[1], HELP_FLAG))
		return (print_error(RETURN_ERROR, USAGE));
	// parse map
	if (map_parser_control(&fdf, argv) == RETURN_ERROR)
		return (print_error(RETURN_ERROR, fdf.error));
	// fdf starts...
	/*
	if (!ft_strequ(argv[1], TEST_PARSER)
		fdf_control()
	*/
	return (RETURN_SUCCESS);
}
