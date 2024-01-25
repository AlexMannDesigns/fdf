/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:57:33 by amann             #+#    #+#             */
/*   Updated: 2023/12/30 13:58:56 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdlib.h>

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
		{
			break ;
		}
		else if (ft_strequ(HELP_FLAG, arg))
		{
			fdf->help = TRUE;
		}
		else if (ft_strequ(TEST_PARSER, arg))
		{
			fdf->test_parser = TRUE;
		}
		else
		{
			return (print_error(FALSE, ERROR_INVALID_OPTION));
		}
		(fdf->path_idx)++;
	}
	return (TRUE);
}

/*
 * Control function for handling any passed cmdline options
 */
static int	flags(t_fdf *fdf, char **argv)
{
	if (!handle_option_flags(fdf, argv))
	{
		return (FALSE);
	}
	if (fdf->help)
	{
		fdf->exit_status = EXIT_SUCCESS;
		print_error(EXIT_SUCCESS, USAGE_LONG);
		return (FALSE);
	}
	if (!(argv[fdf->path_idx]))
	{
		fdf->exit_status = EXIT_SUCCESS;
		print_error(EXIT_SUCCESS, USAGE);
		return (FALSE);
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc == 1)
	{
		return (print_error(EXIT_SUCCESS, USAGE));
	}
	ft_bzero((void *) &fdf, sizeof(t_fdf));
	fdf.exit_status = EXIT_FAILURE;
	if (!flags(&fdf, argv))
	{
		return (fdf.exit_status);
	}
	if (!map_parser_control(&fdf, argv[fdf.path_idx]))
	{
		return (free_and_exit(&fdf));
	}
	if (!(fdf.test_parser))
	{
		fdf_control(&fdf);
	}
	return (free_and_exit(&fdf));
}
