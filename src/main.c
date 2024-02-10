/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amann <amann@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 13:57:33 by amann             #+#    #+#             */
/*   Updated: 2024/02/10 16:07:14 by amann            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdlib.h>

static void	print_long_usage(void)
{
	ft_putstr_fd(USAGE_LONG_0, STDERR_FILENO);
	ft_putstr_fd(USAGE_LONG_1, STDERR_FILENO);
	ft_putstr_fd(USAGE_LONG_2, STDERR_FILENO);
	ft_putstr_fd(USAGE_LONG_3, STDERR_FILENO);
	ft_putstr_fd(USAGE_LONG_4, STDERR_FILENO);
	ft_putstr_fd(USAGE_LONG_5, STDERR_FILENO);
	ft_putstr_fd(USAGE_LONG_6, STDERR_FILENO);
	ft_putstr_fd(USAGE_LONG_7, STDERR_FILENO);
	return ;
}

static int	print_invalid_option(void)
{
	ft_putstr_fd(ERROR_INVALID_OPTION_0, STDERR_FILENO);
	return (print_error(FALSE, ERROR_INVALID_OPTION_1));
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
			return (print_invalid_option());
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
		print_long_usage();
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
