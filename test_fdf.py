from subprocess import run, TimeoutExpired, CompletedProcess
from typing import Final

import pytest

# constants
FDF: Final = "./fdf"
TEST_FLAG: Final = "--test-parser"
HELP_FLAG: Final = "--help"
TIMEOUT: Final = 5
NO_OUTPUT: Final = ""

ERROR_INVALID_OPTION: Final = "Error: invalid option. For help, use './fdf --help'\n"
ERROR_INVALID_FILE: Final = "Error: map file must be plain-text format and have '.fdf' extension\n"
ERROR_INVALID_PERMISSIONS: Final = "Error: map file could not be opened\n"
ERROR_INVALID_VALUES: Final = "Error: map must only contain numeric characters, spaces: ' ', and newlines: '\\n'\n"
ERROR_INVALID_LENGTH: Final = "Error: all lines must be of equal length\n"
USAGE: Final = "Usage:\n./fdf [options...] [path-to-map]\n"
USAGE_LONG: Final = "Welcome to FDF!\n\nUsage:\n./fdf [options...] [path-to-map]\n" \
	"\noptions:\n--help: displays this message\n--test-parser: map will be parsed but fdf window will not open\n" \
	"\npath-to-map:\nMust be a file path to a valid fdf map, with file-extension '.fdf'\n"

# TODO add expected stdout
@pytest.mark.parametrize(
	("path_to_map", "expected_error_output", "expected_return_value"),
	[
		("maps/42.fdf", NO_OUTPUT, 0),
		("maps/abc", ERROR_INVALID_FILE, 1),
		("maps/invalid_permission.fdf", ERROR_INVALID_PERMISSIONS, 1),
		("maps/invalid_values.fdf", ERROR_INVALID_VALUES, 1),
		("maps/unequal_lines.fdf", ERROR_INVALID_LENGTH, 1),

	],
)
def test_maps(path_to_map: str, expected_error_output: str, expected_return_value: int) -> None:
	"""
	Testing steps:
	1. run fdf in subprocess with map file-path
	2. check return value matches expected value
	3. check captured output matches expected output
	"""
	result: None | CompletedProcess = None
	try:
		result = run(
			[FDF, TEST_FLAG, path_to_map],
			timeout=TIMEOUT,
			capture_output=True,
			text=True
		)
	except TimeoutExpired:
		print(f"map: {path_to_map}: timeout expired, please review!")

	assert result is not None
	assert result.returncode == expected_return_value, "Error: incorrect return value"
	assert result.stderr == expected_error_output, "Error: incorrect error message"


@pytest.mark.parametrize(
	("option", "expected_error_output", "expected_return_value"),
	[
		("-", ERROR_INVALID_OPTION, 1),
		("--", ERROR_INVALID_OPTION, 1),
		("---", ERROR_INVALID_OPTION, 1),
		("--abc", ERROR_INVALID_OPTION, 1),
		("-abc", ERROR_INVALID_OPTION, 1),
		(HELP_FLAG, USAGE_LONG, 0),
	],
)
def test_option_flags(option: str, expected_error_output: str, expected_return_value: int) -> None:
	"""
	Testing steps:
	1. run fdf in subprocess with options
	2. check return value matches expected value
	3. check captured output matches expected output
	"""
	result: None | CompletedProcess = None
	try:
		result = run(
			[FDF, option],
			timeout=TIMEOUT,
			capture_output=True,
			text=True
		)
	except TimeoutExpired:
		print(f"Option: {option}: timeout expired, please review!")

	assert result.returncode == expected_return_value, "Error: incorrect return value"
	assert result.stderr == expected_error_output, "Error: incorrect error message"


def test_no_args_prints_usage() -> None:
	result: None | CompletedProcess = None
	try:
		result = run(
			FDF,
			timeout=TIMEOUT,
			capture_output=True,
			text=True
		)
	except TimeoutExpired:
		print(f"Error: {FDF}: timeout expired, please review!")

	assert result.returncode == 0, "Error: incorrect return value"
	assert result.stderr == USAGE, "Error: incorrect error message"
