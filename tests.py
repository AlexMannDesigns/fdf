from subprocess import run
from typing import Final

import pytest


FDF: Final = "fdf"
TEST_FLAG: Final = "--test-parser"
TIMEOUT: Final = 5


@pytest.mark.parametrize(
	("path_to_map", "expected_error_output", "expected_return_value"),
	[
		("maps/42.fdf", None, 0),
	],
)
def test_maps(
	path_to_map: str, expected_error_output: str | None, expected_return_value: int
) -> None:
	try:
		result = run(
			[FDF, TEST_FLAG, path_to_map],
			timeout=TIMEOUT,
			capture_output=True,
			test=True,	
		)
	except TimeoutExpired:
		print(f"map: {path_to_map}: timeout expired, please review!")
	
	assert result.returncode == expected_return_value
	assert result.stderr == expected_error_output

