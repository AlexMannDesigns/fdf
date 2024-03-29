from subprocess import run, TimeoutExpired, CompletedProcess
from typing import Final

import pytest

# constants
FDF: Final = "./fdf"
TEST_FLAG: Final = "--test-parser"
HELP_FLAG: Final = "--help"
VALID_MAP: Final = "maps/42.fdf"
TIMEOUT: Final = 5
NO_OUTPUT: Final = ""
PARAMS: Final = ("option", "expected_output", "expected_error_output", "expected_return_value")

# error messages
ERROR_INVALID_OPTION: Final = "Error: invalid option. For help, use './fdf --help'\n"
ERROR_INVALID_FILE: Final = "Error: map file must be plain-text format and have '.fdf' extension\n"
ERROR_INVALID_PERMISSIONS: Final = "Error: map file could not be opened\n"
ERROR_INVALID_VALUES: Final = "Error: map must only contain numeric characters, spaces: ' ', and newlines: '\\n'\n"
ERROR_INVALID_LENGTH: Final = "Error: all lines must be of equal length\n"
ERROR_NO_VALUES: Final = "Error: no coordinates in file\n"
ERROR_MIN_MAX: Final = "Error: z values must be between INT16_MIN and INT16_MAX\n"
USAGE: Final = "Usage:\n./fdf [options...] [path-to-map]\n"
USAGE_LONG: Final = "Welcome to FDF!\n\nUsage:\n./fdf [options...] [path-to-map]\n" \
	"\noptions:\n--help: displays this message\n--test-parser: map will be parsed but fdf window will not open\n" \
	"\npath-to-map:\nMust be a file path to a valid fdf map, with file-extension '.fdf'\n"


def _run_fdf(args: list | None) -> CompletedProcess | None:
	"""
	Runs fdf with the passed arg list in a sub-process
	"""
	argv: list = [FDF]
	if args is not None:
		argv += args
	result: None | CompletedProcess = None
	try:
		result = run(
			argv,
			timeout=TIMEOUT,
			capture_output=True,
			text=True
		)
	except TimeoutExpired:
		print(f"Error: {args}: timeout expired, please review!")
	return result


@pytest.mark.parametrize(
	("path_to_map", "expected_output", "expected_error_output", "expected_return_value"),
	[
		("maps/abc", NO_OUTPUT, ERROR_INVALID_FILE, 1),
		("maps/", NO_OUTPUT, ERROR_INVALID_FILE, 1),
		(" ", NO_OUTPUT, ERROR_INVALID_FILE, 1),
		("maps/invalid_permission.fdf", NO_OUTPUT, ERROR_INVALID_PERMISSIONS, 1),
		("maps/invalid_values.fdf", NO_OUTPUT, ERROR_INVALID_VALUES, 1),
		("maps/unequal_lines.fdf", NO_OUTPUT, ERROR_INVALID_LENGTH, 1),
		("maps/test.fdf", NO_OUTPUT, ERROR_INVALID_PERMISSIONS, 1),
		("maps/empty.fdf", NO_OUTPUT, ERROR_NO_VALUES, 1),
	],
)
def test_invalid_maps(path_to_map: str, expected_output: str, expected_error_output: str, expected_return_value: int) -> None:
	"""
	Testing steps:
	1. run fdf in subprocess with map file-path
	2. check return value matches expected value
	3. check captured output matches expected output
	"""
	result = _run_fdf([path_to_map])

	assert result is not None, "Error: subprocess failed"
	assert result.returncode == expected_return_value, "Error: incorrect return value"
	assert result.stderr == expected_error_output, "Error: incorrect error message"
	assert result.stdout == expected_output, "Error: incorrect output"


def test_valid_map() -> None:
	"""
	Valid maps should output nothing and return zero with test flag
	"""
	result = _run_fdf([TEST_FLAG, VALID_MAP])

	assert result is not None, "Error: subprocess failed"
	assert result.returncode == 1, "Error: incorrect return value"
	assert result.stderr == NO_OUTPUT, "Error: incorrect error message"
	assert result.stdout == NO_OUTPUT, "Error: incorrect output"


@pytest.mark.parametrize(
	PARAMS,
	[
		("-", NO_OUTPUT, ERROR_INVALID_OPTION, 1),
		("--", NO_OUTPUT, ERROR_INVALID_OPTION, 1),
		("---", NO_OUTPUT, ERROR_INVALID_OPTION, 1),
		("--abc", NO_OUTPUT, ERROR_INVALID_OPTION, 1),
		("-abc", NO_OUTPUT, ERROR_INVALID_OPTION, 1),
		(HELP_FLAG, NO_OUTPUT, USAGE_LONG, 0),
	],
)
def test_option_flags(
		option: str, expected_output: str, expected_error_output: str, expected_return_value: int
) -> None:
	"""
	Testing steps:
	1. run fdf in subprocess with options
	2. check return value matches expected value
	3. check captured output matches expected output
	"""
	result = _run_fdf([option])

	assert result is not None, "Error: subprocess failed"
	assert result.returncode == expected_return_value, "Error: incorrect return value"
	assert result.stderr == expected_error_output, "Error: incorrect error message"
	assert result.stdout == expected_output, "Error: incorrect output"


def test_no_args_prints_usage() -> None:
	"""
	With no args, the program should just print a brief usage msg to stdout
	"""
	result = _run_fdf([TEST_FLAG])

	assert result is not None, "Error: subprocess failed"
	assert result.returncode == 0, "Error: incorrect return value"
	assert result.stderr == USAGE, "Error: incorrect error message"
	assert result.stdout == NO_OUTPUT, "Error: incorrect output"


@pytest.mark.parametrize(
	PARAMS,
	[
		(["-", "--help", VALID_MAP], NO_OUTPUT, ERROR_INVALID_OPTION, 1),
		([" -", "--help", VALID_MAP], NO_OUTPUT, ERROR_INVALID_FILE, 1),
		(["  ", "--help", VALID_MAP], NO_OUTPUT, ERROR_INVALID_FILE, 1),
		(["a", "b", "c", VALID_MAP], NO_OUTPUT, ERROR_INVALID_FILE, 1),
		(["", "", "", " ", "x", "123", VALID_MAP], NO_OUTPUT, ERROR_INVALID_FILE, 1),
		([TEST_FLAG, VALID_MAP, "x", "y", "z", "--", "x", "123"], NO_OUTPUT, NO_OUTPUT, 1),
	],
)
def test_multiple_args(
	option: list, expected_output: str, expected_error_output: str, expected_return_value: int
) -> None:
	"""
	Test ensures that an error is returned when valid params follow invalid params
	Test also ensures an error is not returned with invalid params following valid params
	"""
	result = _run_fdf(option)

	assert result is not None, "Error: subprocess failed"
	assert result.returncode == expected_return_value, "Error: incorrect return value"
	assert result.stderr == expected_error_output, "Error: incorrect error message"
	assert result.stdout == expected_output, "Error: incorrect output"


@pytest.mark.parametrize(
	PARAMS,
	[
		(["maps/max_val_test.fdf"], NO_OUTPUT, ERROR_MIN_MAX, 1),
		(["maps/min_val_test.fdf"], NO_OUTPUT, ERROR_MIN_MAX, 1),
	],
)
def test_min_max(
	option: list, expected_output: str, expected_error_output: str, expected_return_value: int
) -> None:
	"""
	Test ensures that an error is returned when a map with z values over min and max is parsed 
	"""
	result = _run_fdf(option)

	assert result is not None, "Error: subprocess failed"
	assert result.returncode == expected_return_value, "Error: incorrect return value"
	assert result.stderr == expected_error_output, "Error: incorrect error message"
	assert result.stdout == expected_output, "Error: incorrect output"

